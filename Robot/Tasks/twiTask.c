#include "twiTask.h"
#include <util/twi.h>

#define TWI_RECV_BUFLEN 10

static volatile Task* myTask;

// 0=read 1=write
volatile u08 twiMode = 0;

volatile u08 recvIndex = 0;
volatile u08 twiData[TWI_RECV_BUFLEN];

// 0 indicates that we haven't sent anything
volatile u08 txIndex = 0;

void enableTwiTask() {
	myTask = addTask(runTWI);
	(*myTask).interval = 100;
}

void disableTwiTask() {
	removeTask((*myTask).index);
}
/**
 * preps system to send data, if we have any
 */
void handleReadRequest() {
	if (txIndex==0) {
		// TODO: 
	}
}

void handleWriteComplete() {
	if (recvIndex > 0) { // this should always be the case

	}
}


void runTWI() {
	if (gbi(TWCR, TWINT)) {
		switch(TW_STATUS) {
		case TW_SR_SLA_ACK: 		// SLA+W received, ACK returned
			recvIndex = 0;		// reset the buffer index
			twiMode = 1;		// save that we are being written to
			sbi(TWCR, TWEA);
			break;

		case TW_SR_DATA_ACK:		// data received, ACK returned
			twiData[recvIndex] = TWDR;
			if (++recvIndex == TWI_RECV_BUFLEN)
				cbi(TWCR, TWEA);

		case TW_SR_STOP:			// stop or repeated start condition received
			if (twiMode)			// twiMode=1 when writting
				handleWriteComplete();

			sbi(TWCR, TWEA);
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

		// we have to do this manually... :(
		sbi(TWCR, TWINT); 		// clear interrupt flag
	}
}