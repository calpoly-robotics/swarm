#ifndef IR_H
#define IR_H
#include "globals.h"

#define BUFFER_SIZE 10
#define NUM_NIBBLES 10
#define HIGH_WIDTH 200
#define LOW_WIDTH 200
#define RESOLUTION 20
#define TIMEOUT 1000

#define TRANSMIT_PIN 4
#define TRANSMIT_ON() (sbi(PORTA, TRANSMIT_PIN))
#define TRANSMIT_OFF() (cbi(PORTA, TRANSMIT_PIN))
#define TRANSMIT_STATE() (gbi(PORTA, TRANSMIT_PIN))
#define TRANSMIT_OUTPUT() (sbi(DDRA, TRANSMIT_PIN))
#define RECEIVE_PIN 3
#define RECEIVE_STATE() (gbi(PINA, RECEIVE_PIN))
#define RECEIVE_INPUT() (cbi(DDRA, RECEIVE_PIN))

typedef struct {
	u08 sender; 	// 7 bits
	u08 isBase; 	// 1 bit
	u08 origSend;	// 1 bit
	u08 direction;	// 3 bits
	u08 hopCount;	// 3 bits
	u08 msg; 		// 8 bits
	u08 data; 		// 8 bits
} Message;

void initIR(void);
void sendMessage(u08 hop, msg_type msg, u08 data);
void manageTransmit(void);

#endif