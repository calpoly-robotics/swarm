#include "motor.h"
#include "../pins.h"

void initMotor() 
{
	sbi(DDRD, MOTOR_STANDBY);
	sbi(PORTD, MOTOR_STANDBY);

	sbi(DDRD, LEFT_MOTOR_BIN1);
	cbi(PORTD, LEFT_MOTOR_BIN1);
	sbi(DDRD, LEFT_MOTOR_BIN2);
	cbi(PORTD, LEFT_MOTOR_BIN2);
	sbi(DDRD, LEFT_MOTOR_SIGNAL);
	cbi(PORTD, LEFT_MOTOR_SIGNAL);

	sbi(DDRD, RIGHT_MOTOR_AIN1);
	cbi(PORTD, RIGHT_MOTOR_AIN1);
	sbi(DDRC, RIGHT_MOTOR_AIN2);
	cbi(PORTC, RIGHT_MOTOR_AIN2);
	sbi(DDRD, RIGHT_MOTOR_SIGNAL);
	cbi(PORTD, RIGHT_MOTOR_SIGNAL);

	// waveform generation mode: fast pwm
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	cbi(TCCR2B, WGM22);

	// configure waveform 
	cbi(TCCR2A, COM2A0);
	sbi(TCCR2A, COM2A1);
	cbi(TCCR2A, COM2B0);
	sbi(TCCR2A, COM2B1);

	// start the clock
	sbi(TCCR2B, CS20);
}

void shutdownMotor() {
	cbi(PORTD, MOTOR_STANDBY);

	cbi(DDRD, LEFT_MOTOR_BIN1);
	sbi(PORTD, LEFT_MOTOR_BIN1);
	cbi(DDRD, LEFT_MOTOR_BIN2);
	sbi(PORTD, LEFT_MOTOR_BIN2);
	cbi(DDRD, LEFT_MOTOR_SIGNAL);
	sbi(PORTD, LEFT_MOTOR_SIGNAL);

	cbi(DDRD, RIGHT_MOTOR_AIN1);
	sbi(PORTD, RIGHT_MOTOR_AIN1);
	cbi(DDRC, RIGHT_MOTOR_AIN2);
	sbi(PORTC, RIGHT_MOTOR_AIN2);
	cbi(DDRD, RIGHT_MOTOR_SIGNAL);
	sbi(PORTD, RIGHT_MOTOR_SIGNAL);
}

void leftMotor(s16 speed)
{
	if (speed > 0 ) {
		cbi(PORTD, LEFT_MOTOR_BIN1); // AIN1
		sbi(PORTD, LEFT_MOTOR_BIN2); // AIN2
		OCR2B = speed;
	} else if (speed < 0) {
		sbi(PORTD, LEFT_MOTOR_BIN1);
		cbi(PORTD, LEFT_MOTOR_BIN2);
		OCR2B = (u08) (speed*-1);
	} else {
		cbi(PORTD, LEFT_MOTOR_BIN1);
		cbi(PORTD, LEFT_MOTOR_BIN2);
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