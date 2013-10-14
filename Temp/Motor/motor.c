#include "motor.h"

void initMotor()
{
	cbi(PORTD, 5); // AIN1
	sbi(DDRD, 5); // Data Direction Register <Letter (D)>, <#>
	cbi(PORTC, 0); // AIN2
	sbi(DDRC, 0); 
	cbi(PORTD, 7); // APWM
	sbi(DDRD, 7); 
	
	cbi(PORTD, 3); // BIN1
	sbi(DDRD, 3); 
	cbi(PORTD, 2); // BIN2
	sbi(DDRD, 2); 
	cbi(PORTD, 6); // BPWM
	sbi(DDRD, 6); 
	
	cbi(PORTD, 4); // STBY
	sbi(DDRD, 4);
	
	// set bit WGM20 & WGM21
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	cbi(TCCR2A, WGM22);

	// set bit COM0A1
	cbi(TCCR2A, COM2A0);
	sbi(TCCR2A, COM2A1);
	// set bit COM0B1
	cbi(TCCR2A, COM2B0);
	sbi(TCCR2A, COM2B1);

	// set clock select bit CS20 & CS21
	TCCR2B = 0x03;
}