#ifndef IR_H
#define IR_H
#include "globals.h"

typedef struct {
	u08 sender; // 7 bits
	u08 flags; // 8 bit - direction(3), isBase(1), hopCount(3), origSend(1) 
	u08 checksum; // 4 bits
	u08 sequence; // 8 bits
	u08 msg; // 8 bits
	u08 data; // 8 bits
} Message;

void initIR(void);
void sendMessage(Message msg);
void manageTransmit(void);

#endif