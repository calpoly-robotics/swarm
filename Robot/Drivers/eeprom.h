#ifndef EEPROM_H_
#define EEPROM_H_ 1

#include <avr/eeprom.h>
#include "../globals.h"

// true for both 1281 and 1284
#define EEPROM_MAX_ADDRESS 4096

// can be changed to whatever we feel like
#define IR_SENDER_ID_ADDRESS 0

// just use the ir_sender_id_address
// #define TWI_ID_ADDRESS 1 // 7 bits

#define DATA_LOGGING_START_ADDRESS 64

void eepromLogByte(u08 data);
void eepromLogBlock(u08* data, size_t len);

void eepromLogChar(u08 data);
void eepromLogString(u08* str);

u08* eepromReadLog(size_t* len);


#endif