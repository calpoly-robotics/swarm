#include "../globals.h"

void initClock()
{
	// initialize to zero
	upper16 = 0;
	
	// clear bits
	cbi(TCCR3A, WGM30);
	cbi(TCCR3A, WGM31);
	cbi(TCCR3B, WGM32);
	cbi(TCCR3B, WGM33);
	
	// clear bit COM3A
	cbi(TCCR3A, COM3A0);
	cbi(TCCR3A, COM3A1);
	// clear bit COM3B
	cbi(TCCR3A, COM3B0);
	cbi(TCCR3A, COM3B1);
	
	// set Overflow interrupt enable bit
	sbi(TIMSK3, TOIE3);

	// set clock select bit CS30 & CS32
	sbi(TCCR3B, CS30);
	cbi(TCCR3B, CS31);
	sbi(TCCR3B, CS32);
	
	// point to upper and lower bits of time
	lpoint = (u16*)&time;
	upoint = (u16*)&time + 1;
}

void getTime32()
{
	*upoint = upper16;
	*lpoint = TCNT3;
}

ISR(TIMER3_OVF_vect)
{
	upper16++;
}