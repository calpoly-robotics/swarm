#include "globals.h"
#include <util/parity.h>

inline void enableOCR(u08 val)
{
	TCNT2 = 0x00;
	OCR2A = val;
	sbi(TIFR2, 1); // prevent immediate interrupt
	TIMSK2 = 0x02; // turn on OCR1A interrupt
}

inline void disableOCR()
{
	TIMSK2 = 0x00; // turn off OCR1A interrupt
}

void enablePCINT()
{
	PCICR = 0x08;
	PCMSK3 = 0x02;
}

void disablePCINT()
{
	PCICR = 0x00;
	PCMSK3 = 0x00;
}

// timer interrupt
ISR(TIMER2_COMPA_vect)
{
	cbi(PORTD, 0);
	disableOCR();
}

ISR(PCINT3_vect)
{
	if (gbi(PIND, 1))
		return;
	
	
	sbi(PORTD, 0);
	enableOCR(19);
	// if (!gbi(PIND, 1))
	// {
		// tbi(PORTB, 0);
	// }
}

void init()
{
	TCCR2A = 0x02; // CTC mode
	TCCR2B = 0x03; // CTC mode and clk/32 prescaler
	TIMSK2 = 0x00; // turn off OCR2A interrupt
	
	cbi(DDRD, 1); // set PD1 as input
	sbi(PORTD, 1); // turn on pull-up
	
	sbi(DDRD, 0); // RX pin as output for debug
	cbi(PORTD, 0);
	
	enablePCINT();
	sei();
}

int main()
{
	init();
	while(1);
}
