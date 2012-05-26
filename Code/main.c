#include "globals.h"
#include "messages.h"
#include "ir.h"


void init() {
	sbi(DDRB, RED_LED); // IR out as output
	sbi(DDRB, GREEN_LED); // green LED as output
	cbi(DDRB, SENSOR_PIN); // set receiver pin as input
	uartInit();
}

int main()
{
	u08 mess[MAX_MESSAGESIZE];
	init();
	Message msg;
	msg.sender = 0x55;
	msg.hopCount = 0;
	msg.origSend = 1;
	msg.message = IM_HERE;
	msg.isBase = 0;
	msg.type = MESSAGE;
	
	cbi(PORTB, RED_LED);
	while (1) {
		sendMessage(msg);
		doSend();
		sbi(PORTB, RED_LED);
		_delay_ms(10);
		cbi(PORTB, RED_LED);
	}
}
