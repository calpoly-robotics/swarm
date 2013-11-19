#include <math.h>

#include "buzzer.h"
#include "../pins.h"

u16 tempo;

u08 driverState = 0;
u08 count = 0;
u08 playTime = 0;

#if 1
void initBuzzer() {
	sbi(DDRB, BUZZER_PIN);

	// toggle pin on OC1A
	sbi(TCCR1A, COM3A0);
	cbi(TCCR1A, COM3A1);

	sbi(DDRB, 2);

	/*
	// fast PWM mode
	sbi(TCCR1A, WGM30);
	sbi(TCCR1A, WGM31);
	sbi(TCCR1B, WGM32);
	sbi(TCCR1B, WGM33);
	*/

	// CTC
	sbi(TCCR1B, WGM12);

	// 1/8 prescaler
	sbi(TCCR1B, CS11);

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
	TCNT1H = 0;
	TCNT1L = 0;

	u16 ticks = noteToCycles(note);
	OCR1AH = ticks >> 8;
	OCR1AL = ticks & 0x0F;

	//enable interrupt
	sbi(TIMSK1, OCIE1A);

	playTime = len;
}

ISR(TIMER1_COMPA_vect) {
	if (driverState) {
		cbi(PORTB, BUZZER_PIN);
		cbi(PORTB, 2);
		driverState = 0;
	} else {
		sbi(PORTB, BUZZER_PIN);
		cbi(PORTB, 2);
		driverState = 1;
	}
}
#endif
