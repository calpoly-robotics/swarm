#include "globals.h"

u16 test = 0;

int main()
{
	initIR();
	uartInit();
	sbi(DDRB, 2);
	uartPrintString("HELLO!\r\n");
	_delay_ms(2000);
	
	while (1)
	{
		// sendMessage(2, IM_HERE, 0x55);
		// manageTransmit();
		// _delay_us(400);
		manageReceive();
		_delay_ms(1);
		tbi(PORTB, 2);
	}
}
