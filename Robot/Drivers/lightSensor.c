#include "lightSensor.h"
#include "adc.h"
#include "../pins.h"

void initLightSensor() {
	cbi(DDRA, LIGHT_SENSOR);
	sbi(PORTA, LIGHT_SENSOR);
}

u16 readLightSensor() {
	return readADC(LIGHT_SENSOR);
}