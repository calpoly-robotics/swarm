#include "globals.h"

int main()
{
	sbi(DDRB, 0); // IR out as output
	sbi(DDRB, 1); // green LED as output
	cbi(DDRB, SENSOR_PIN); // set receiver pin as input
	uartInit();
	
	sbi(PORTB, 0);
	_delay_ms(500);
	cbi(PORTB, 0);
	
	while(1)
	{
		uart0PrintString("Hello World!\r");
		_delay_ms(100);
	}
}