#ifndef TWI_H_
#define TWI_H_ 1

typedef enum {
	WHOS_THERE,
	IM_HERE,
	DUMP_DATA,
	NUM_MESSAGES
} twi_msg_type;

void enableTwi();
void disableTwi();

void handleMsg();

#endif