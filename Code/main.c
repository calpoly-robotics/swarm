#include "globals.h"

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
	
	while (1)
	{
	}
}
