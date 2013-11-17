#include "twi.h"
#include "eeprom.h"
#include "../globals.h"
#include <util/twi.h>

void enableTwi() {
	// load up the address and set it to register
	u08 address = eeprom_read_byte((u08*)IR_SENDER_ID_ADDRESS);
	TWAR = address << 1;

	// sbi(TWCR, TWINT); // clear the interrupt flag
	sbi(TWCR, TWEN); // enable tiw
	sbi(TWCR, TWEA); //enable ack
	// sbi(TWCR, TWIE); // enable the interrupt

	sei();
}

void disableTwi() {
	cbi(TWCR, TWEN);
}
