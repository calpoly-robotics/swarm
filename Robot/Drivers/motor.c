#include "motor.h"
#include "../pins.h"

void initMotor() 
{
	sbi(DDRD, LEFT_MOTOR_AIN1);
	cbi(PORTD, LEFT_MOTOR_AIN1);
	sbi(DDRC, LEFT_MOTOR_AIN2);
	cbi(PORTC, LEFT_MOTOR_AIN2);
	sbi(DDRD, LEFT_MOTOR_SIGNAL);
	cbi(PORTD, LEFT_MOTOR_SIGNAL);

	sbi(DDRD, RIGHT_MOTOR_AIN1);
	cbi(PORTD, RIGHT_MOTOR_AIN1);
	sbi(DDRD, RIGHT_MOTOR_AIN2);
	cbi(PORTD, RIGHT_MOTOR_AIN2);
	sbi(DDRD, RIGHT_MOTOR_SIGNAL);
	cbi(PORTD, RIGHT_MOTOR_SIGNAL);

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
		cbi(PORTD, LEFT_MOTOR_AIN1); // AIN1
		sbi(PORTC, LEFT_MOTOR_AIN2); // AIN2
		OCR2B = speed;
	} else if (speed < 0) {
		sbi(PORTD, LEFT_MOTOR_AIN1);
		cbi(PORTC, LEFT_MOTOR_AIN2);
		OCR2B = (u08) (speed*-1);
	} else {
		cbi(PORTD, LEFT_MOTOR_AIN1);
		cbi(PORTC, LEFT_MOTOR_AIN2);
	}
}

void rightMotor(s16 speed)
{
	if (speed > 0 ) {
		cbi(PORTD, RIGHT_MOTOR_AIN1); // BIN1
		sbi(PORTC, RIGHT_MOTOR_AIN2); // BIN2
		OCR2A = speed;
	} else if (speed < 0) {
		sbi(PORTD, RIGHT_MOTOR_AIN1);
		cbi(PORTC, RIGHT_MOTOR_AIN2);
		OCR2A = (u08) (speed*-1);
	} else {
		cbi(PORTD, RIGHT_MOTOR_AIN1);
		cbi(PORTC, RIGHT_MOTOR_AIN2);
	}
}