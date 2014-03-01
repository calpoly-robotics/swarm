#ifndef IR_H_
#define IR_H_

#include "../globals.h"
#include "../pins.h"

#define BUFFER_SIZE 10
#define NUM_NIBBLES 10
// time for collector to go high
#define HIGH_WIDTH 200
// time for collector to fall low
#define LOW_WIDTH 200
#define RESOLUTION 20
// 15*Res for max message + Res because + low in tx + high cuz needs rise and fall
// TODO: The 100 could be as low as Resolution. Needs revisiting
#define TIMEOUT ((0x0F+1)*RESOLUTION + HIGH_WIDTH + LOW_WIDTH + 100)

#define TRANSMIT_ON() (sbi(PORTC, TRANSMIT_PIN))
#define TRANSMIT_OFF() (cbi(PORTC, TRANSMIT_PIN))
#define TRANSMIT_STATE() (gbi(PORTC, TRANSMIT_PIN))

#define DEFAULT_MESSAGE (*((Message*)NULL))

typedef enum {
	WHOS_THERE,
	IM_HERE,
	NUM_MSGS
} msg_type;

typedef struct {
	u08 sender; 	// 7 bits
	u08 isBase; 	// 1 bit
	u08 origSend;	// 1 bit
	u08 direction;	// 3 bits
	u08 ttl;		// 3 bits
	u08 msg; 		// 8 bits
	u08 data; 		// 8 bits
} Message;

void initIR(void);
void sendMessage(u08 hop, msg_type msg, u08 data);
void manageTransmit(void);
void manageRecieve(void);
int readMessage(Message*);
u08 getRecvBufCount();
u08 getSenderId(void);


#endif