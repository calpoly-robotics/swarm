#include "messages.h"
#include "ir.h"

void init()
{
	sbi(DDRB, RED_LED); // IR out as output
	sbi(DDRB, GREEN_LED); // green LED as output
	cbi(DDRB, SENSOR_PIN); // set receiver pin as input
	uartInit();
}

int main()
{
	init();
	initIR();
	
	Message msg = {0x55, 0, 1, IM_HERE, 0, MESSAGE};
	
	while (1)
	{
		sendMessage(msg);
		manageTransmit();
		sbi(PORTB, RED_LED);
		_delay_ms(10);
		cbi(PORTB, RED_LED);
	}
}
