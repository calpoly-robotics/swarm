#include "lightSensor.h"
#include "adc.h"

void initLightSensor() {
	cbi(DDRA, 5);
	sbi(PORTA, 5);
}

u16 readLightSensor() {
	return readADC(5);
}