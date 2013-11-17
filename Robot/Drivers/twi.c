#include "twi.h"
#include "eeprom.h"
#include "../globals.h"
#include <util/twi.h>

void twiInit() {
	// load up the address and set it to register
	u08 address = eeprom_read_byte((u08*)IR_SENDER_ID_ADDRESS);
	TWAR = address << 1;

	sbi(TWCR, TWINT); // clear the interrupt flag
	sbi(TWCR, TWEN); // enable tiw
	sbi(TWCR, TWEA); //enable ack
	sbi(TWCR, TWIE); // enable the interrupt

	sei();
}

volatile u08 twiData;

// SLA is a "start"
// SLA+R/W determines what the master is doing

ISR(TWI_vect) {
	u08 twi_status;

	cli();

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
	}

	// we have to do this manually... :(
	sbi(TWCR, TWINT); 		// clear interrupt flag


	sei();
}
