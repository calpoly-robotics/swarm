#include "clock.h"

volatile u16 upper16;

void initClock() {

	/* 
	// set timer to "normal" waveform generation mode
	// don't bother making a wave
	cbi(TCCR3A, WGM30);
	cbi(TCCR3A, WGM31);
	cbi(TCCR3A, WGM32);
	cbi(TCCR3A, WGM33);

	// turn off Output Compare
	cbi(TCCR3A, COM3A0);
	cbi(TCCR3A, COM3A1);
	cbi(TCCR3A, COM3B0);
	cbi(TCCR3A, COM3B1);
	*/

	// Enable the overflow interrupt
	sbi(TIMSK3, TOIE3);

	// Set prescaller to 1/1024 (~10kHz)
	sbi(TCCR3B, CS30);
	sbi(TCCR3B, CS32);

}

u32 getTime32() {
	u32 time = TCNT3;
	time |= ((u32)upper16) << 16;

	return time;
}

ISR(TIMER3_OVF_vect) {
	upper16++;
}