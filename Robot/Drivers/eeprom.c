#include "eeprom.h"


volatile u16 lastWriteAddress = DATA_LOGGING_START_ADDRESS;

void eepromLogByte(u08 data) {

}


void eepromLogBlock(u08* data, size_t len) {

}

void eepromLogChar(u08 data) {

}

void eepromLogString(u08* str) {

}

u08* eepromReadLog(size_t* len) {
	if (lastWriteAddress == DATA_LOGGING_START_ADDRESS)	// no data logged
		return NULL;

	*len = lastWriteAddress - DATA_LOGGING_START_ADDRESS;
	u08* data = malloc(sizeof(u08) * (*len)); // allocate enough memory

	eeprom_read_block(data, (void*)DATA_LOGGING_START_ADDRESS, *len);
	return data;
}
