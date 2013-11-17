#include "twiTask.h"

static volatile Task* myTask;

void enableTwiTask() {
	myTask = addTask(runTWI);
	(*myTask).interval = 100
}

void disableTwiTask() {

}


void runTWI() {
	u08 twi_status;

	// get the twi state and mask out the prescaler
	twi_status = TWSR & 0xF8

	switch(twi_status) {
	case TW_SR_SLA_ACK: 		// SLA+W received, ACK returned
		// TODO: handle what the base is trying to tell us...
		break;
	case TW_SR_DATA_ACK:		// data received, ACK returned
		twiData = TWDR;		// save data to the register addr
	case TW_SR_STOP:			// stop or repeated start condition received
		// TODO: handle this..
		break;
	case TW_ST_SLA_ACK:			// SLA+R received, ACK returned
	case TW_ST_DATA_ACK:		// data tx, ACK received
		// TODO: handle this...
		break;

	case TW_ST_DATA_NACK:		// data transmitted, NACK received
	case TW_ST_LAST_DATA:		// last data byte tx, ACK received.
	case TW_BUS_ERROR:			// illegal start or stop condition..
	default:
		
	}

	// we have to do this manually... :(
	sbi(TWCR, TWINT); 		// clear interrupt flag

}