#include "globals.h"

int main()
{
	sbi(DDRB, 0); // IR out as output
	sbi(DDRB, 1); // green LED as output
	cbi(DDRB, SENSOR_PIN); // set receiver pin as input
	
	while(1)
	{
		if (gbi(PORTB, SENSOR_PIN))
		{
			tbi(PORTB, 0);
		}
		else
		{
			tbi(PORTB, 1);
		}
_delay_ms(100);
	}
}