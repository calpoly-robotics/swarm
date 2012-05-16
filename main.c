#include "globals.h"

void initTimer1()
{
	TCCR1A = 0x00;
	TCCR1B = 0x02;
}

void initPCint()
{
	PCMSK0 = 0x04;
	sendPulse();
	sei();
}

ISR(PCINT0_vect)
{
	cli();
	if(gbi(PINB, SENSOR_PIN))
	{
		TCNT1 = 0x0000;
	}
	else
	{
		time = TCNT1;
	}
	sei();
}

int main()
{
	sbi(DDRB, 0);
	sbi(DDRB, 1);
	tbi(PORTB, 0);
	while(1) 
	{
		tbi(PORTB, 0);
		tbi(PORTB, 1);
		_delay_ms(100);
	}
}