#include "distance.h"
#include "../pins.h"

void initDistanceSensor() {
	sbi(DDRA, DISTANCE_SENSOR);
	cbi(PORTA, DISTANCE_SENSOR);
	cbi(DDRA, DISTANCE_EMITTER);
}

u16 readDistanceSensor() {
	sbi(PORTA, DISTANCE_SENSOR);
	u16 val = readADC(DISTANCE_EMITTER);
	cbi(PORTA, DISTANCE_SENSOR);
	return val;
}