#include "distance.h"
#include "../pins.h"

void initDistanceSensor() {
	sbi(DDRA, DISTANCE_EMITTER);
	cbi(PORTA, DISTANCE_EMITTER);
	cbi(DDRA, DISTANCE_SENSOR);
}

u16 readDistanceSensor() {
	sbi(PORTA, DISTANCE_EMITTER);
	_delay_us(10);
	u16 val = readADC(DISTANCE_SENSOR);
	cbi(PORTA, DISTANCE_EMITTER);
	return val;
}