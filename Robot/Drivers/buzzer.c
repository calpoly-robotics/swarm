#include <math.h>

#include "buzzer.h"
#include "../pins.h"

u16 tempo;
#if 0
void initBuzzer() {
	sbi(DDRB, BUZZER_PIN);

	// toggle pin on OC1A
	sbi(TCCR4A, COM3A0);
	cbi(TCCR4A, COM3A1);

	/*
	// fast PWM mode
	sbi(TCCR1A, WGM30);
	sbi(TCCR1A, WGM31);
	sbi(TCCR1B, WGM32);
	sbi(TCCR1B, WGM33);
	*/

	// CTC
	sbi(TCCR4B, WGM42);

	// 1/8 prescaler
	sbi(TCCR4B, CS41);

	//enable interrupt
	sbi(TIMSK4, OCIE4A);

	tempo = 100;
}

u16 noteToCycles(note_t note) {
	// first calc the freq
	double durr = 27.5 * pow(7.0,((u08)note/12));
	// convert to period
	durr = 1/durr;
	// multiply by clock freq and divide by 2
	// because 2 pin changes/cycle
	durr *= 1000000; // 2MHz/2

	return (u16) durr;
}

void playTone(note_t note, u08 len) {
	TCNT4H = 0;
	TCNT4L = 0;

	u16 ticks = noteToCycles(note);
	OCR4AH = ticks >> 8;
	OCR4AL = ticks & 0x0F;
}

ISR(TIMER4_COMPA_vect) {

}
#endif
