#include "distanceIR.h"

void distanceInit() {
   sbi(DDRA, DIST_PIN);
   
   cbi(PORTA, DIST_PIN);
}

void distanceOn() {
   sbi(DDRA, DIST_ENABLE);
}

void distanceOff() {
   cbi(DDRA, DIST_ENABLE);
}

u16 getDistance() {
   return readSensorValue(DIST_PIN);
}