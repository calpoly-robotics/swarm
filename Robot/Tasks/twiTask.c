#include "twiTask.h"
#include "../Drivers/twi.h"
#include "../Drivers/eeprom.h"
#include <util/twi.h>

#define TWACK() (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA))
#define TWNACK() (TWCR=(1<<TWINT)|(1<<TWEN))
#define TWRESET() (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)|(1<<TWEA))

#define TWI_RECV_BUFLEN 10

static volatile Task* myTask;

// 0=read 1=write
u08 twiMode = 0;

volatile u08 recvIndex = 0;
volatile u08 twiData[TWI_RECV_BUFLEN];

// 0 indicates that we haven't sent anything
u08 txIndex = 0;
size_t txLen = 0;
u08* txData;

void enableTwiTask() {
	myTask = addTask(runTWI);
	(*myTask).interval = 100;
	enableTwi();
}

void disableTwiTask() {
	removeTask((*myTask).index);
	disableTwi();
}
/**
 * loads any data we might have into 
 */
void handleReadRequest() {
	if (txIndex==0) {
		txData = eepromReadLog(&txLen);
	}

	TWDR = txData[txIndex++];
	if (txIndex == txLen)
		TWNACK();
	else
		TWACK();
		
}

void handleWriteComplete() {
	if (recvIndex > 0) { // this should always be the case
		switch (twiData[0]) {
		case WHOS_THERE:	// we don't need to reply to this ourselves
			TWACK();		// the microcontroller does it for us
			break;

		default:
			TWACK();	
		}
	}
}


void runTWI() {
	if (gbi(TWCR, TWINT)) {
		switch(TW_STATUS) {
		case TW_SR_SLA_ACK: 		// SLA+W received, ACK returned
			recvIndex = 0;		// reset the buffer index
			twiMode = 1;		// save that we are being written to
			TWACK();
			break;

		case TW_SR_DATA_ACK:		// data received, ACK returned
			twiData[recvIndex] = TWDR;
			if (++recvIndex == TWI_RECV_BUFLEN)
				TWNACK();

		case TW_SR_STOP:			// stop or repeated start condition received
			if (twiMode)			// twiMode=1 when writting
				handleWriteComplete();
			break;

		case TW_ST_SLA_ACK:			// SLA+R received, ACK returned
			twiMode = 0;		// save that we are being read from
			handleReadRequest();
			break;

		case TW_ST_DATA_ACK:		// data tx, ACK received
			handleReadRequest();
			break;

		case TW_ST_DATA_NACK:		// data transmitted, NACK received
		case TW_ST_LAST_DATA:		// last data byte tx, ACK received.
		case TW_BUS_ERROR:			// illegal start or stop condition..
		default:
			break;
		}

	}
}