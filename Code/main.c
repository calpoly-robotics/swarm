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
	
	cbi(PORTB, RED_LED);
	while (1) {
		createMessage(mess, 0x55, 0, 1, IM_HERE);
		sendMessage(mess);
		sbi(PORTB, RED_LED);
		_delay_ms(1000);
		cbi(PORTB, RED_LED);
	}
}
