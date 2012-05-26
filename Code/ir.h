#ifndef IR_H
#define IR_H
#include "globals.h"

typedef enum {
	MESSAGE = 2,
	ANALOG_DETECTION = 3,
	DIGITAL_DETECTION = 4
} MessageType;

typedef struct {
	u08 sender;
	u08 hopCount;
	u08 origSend;
	u08 message;
	u08 isBase; // 0 is robot, 1 is base
	MessageType type;
} Message;

/*u08 *createMessage(u08 sender, u08 hopCount, u08 origSend, u08 message);
void sendMessage(u08* buf);*/

void sendMessage(Message);
void doSend(void);

#endif