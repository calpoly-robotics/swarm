#include "motor.h"

void initMotor() 
{
	sbi(DDRD, 5);
	cbi(PORTD, 5);
	sbi(DDRC, 0);
	cbi(PORTC, 0);
	sbi(DDRD, 7);
	cbi(PORTD, 7);

	sbi(DDRD, 3);
	cbi(PORTD, 3);
	sbi(DDRD, 2);
	cbi(PORTD, 2);
	sbi(DDRD, 6);
	cbi(PORTD, 6);

	// waveform generation mode: fast pwm
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	cbi(TCCR2A, WGM22);

	// configure waveform 
	cbi(TCCR2A, COM2A0);
	sbi(TCCR2A, COM2A1);
	cbi(TCCR2A, COM2B0);
	sbi(TCCR2A, COM2B1);
}

void leftMotor(s16 speed)
{
	if (speed > 0 ) {
		cbi(PORTD, 3); // AIN1
		sbi(PORTC, 2); // AIN2
		OCR2B = speed;
	} else if (speed < 0) {
		sbi(PORTD, 3);
		cbi(PORTC, 2);
		OCR2B = (u08) (speed*-1);
	} else {
		cbi(PORTD, 3);
		cbi(PORTC, 2);
	}
}

void rightMotor(s16 speed)
{
	if (speed > 0 ) {
		cbi(PORTD, 5); // AIN1
		sbi(PORTC, 0); // AIN2
		OCR2A = speed;
	} else if (speed < 0) {
		sbi(PORTD, 5);
		cbi(PORTC, 0);
		OCR2A = (u08) (speed*-1);
	} else {
		cbi(PORTD, 5);
		cbi(PORTC, 0);
	}
}