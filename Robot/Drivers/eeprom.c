#include "eeprom.h"


void* lastWriteAddress = (void*)DATA_LOGGING_START_ADDRESS - 1;

/**
 * Returns 1 if there is enough space left
 */
u08 checkHasSpace(size_t spaceWanted) {
	if ((EEPROM_MAX_ADDRESS - (int)lastWriteAddress) < spaceWanted)
		return 0;

	return 1;
}

u08 eepromLogByte(u08 data) {
	size_t size = sizeof(u08);

	if (!checkHasSpace(size))
		return 0;

	eeprom_update_byte(++lastWriteAddress, data);
	lastWriteAddress += (size -1);
	return 1;
}

u08 eepromLogBlock(u08* data, size_t len) {
	size_t size = sizeof(u08) * len;

	if (!checkHasSpace(size))
		return 0;

	eeprom_update_block(data, ++lastWriteAddress, len);
	lastWriteAddress += (size -1);
	return 1;
}

u08* eepromReadLog(size_t* len) {
	if ((int)lastWriteAddress < DATA_LOGGING_START_ADDRESS)	// no data logged
		return NULL;

	*len = (int)lastWriteAddress - DATA_LOGGING_START_ADDRESS + 1;
	u08* data = malloc(sizeof(u08) * (*len)); // allocate enough memory

	eeprom_read_block(data, (void*)DATA_LOGGING_START_ADDRESS, *len);
	return data;
}
