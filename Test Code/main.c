#include "globals.h"

void init()
{
	sbi(DDRB, RED_LED); // red LED out as output
}

int main()
{
	init();
	
	while (1)
	{
		sbi(PORTB, RED_LED);
		_delay_ms(200);
		cbi(PORTB, RED_LED);
		_delay_ms(2);
	}
}
