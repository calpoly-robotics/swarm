#include "adc.h"
#include "../globals.h"

// millivolts
#define VREF 2560

void initADC() {
	sbi(ADMUX, 7);
	sbi(ADMUX, 6);

	//enable
	sbi(ADCSRA, 7);

	// set prescaler to 16
	sbi(ADCSRA, 0);
	sbi(ADCSRA, 2);
}

u16 readADC(u08 pin) {
	// clear and write the pin number to register
	cbi(ADMUX, 0);
	cbi(ADMUX, 1);
	cbi(ADMUX, 2);
	ADMUX |= (pin & 0x07);

	//set bit 6 to start conversion
	sbi(ADCSRA, 6);

	// loop until  bit 6 is cleared, indicating 
	// conversion is complete
	while (gbi(ADCSRA,6) != 0);

	return ADC*VREF;
}