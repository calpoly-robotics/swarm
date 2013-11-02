#include "motor.h"

void initMotor() 
{
	// waveform generation mode: fast pwm
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	cbi(TCCR2A, WGM22);

}

void leftMotor(s16 speed)
{
	if (speed > 0 ) {
		cbi(PORTD, 3); // AIN1
		sbi(PORTC, 2); // AIN2
		OCR2B = speed;
	} else if (spped < 0) {
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
	} else if (spped < 0) {
		sbi(PORTD, 5);
		cbi(PORTC, 0);
		OCR2A = (u08) (speed*-1);
	} else {
		cbi(PORTD, 5);
		cbi(PORTC, 0);
	}
}