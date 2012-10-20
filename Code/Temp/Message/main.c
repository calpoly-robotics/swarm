#include "globals.h"


void init()
{
	sbi(IR_LED_DDR, IR_LED_PIN); // IR out as output
	sbi(DDRB, RED_LED); // green LED as output
	cbi(DDRA, 3);
	sbi(DDRA, 2);
}

int main()
{
	init();
	sbi(PORTB, RED_LED);
	_delay_ms(500);
	cbi(PORTB, RED_LED);
	initIR();
	
#if (IS_RECEIVER == 1)
	uartInit();
#endif
	
#if (IS_RECEIVER == 0)
	Message msg = {0x55, 0, 1, 0, 1};
#endif
	
	while (1)
	{
#if (IS_RECEIVER == 0)
		sendMessage(msg);
		manageTransmit();
		_delay_ms(1000);
#endif

#if (IS_RECEIVER == 1)
		doTest();
		_delay_ms(100);
#endif
	}
}
