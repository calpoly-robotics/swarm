#include "lightSensor.h"

void lightInit() {
   cbi(DDRA, LIGHT_PIN);
   
   sbi(PORTA, LIGHT_PIN);
}

u16 getLightSensorValue() {
   return readSensorValue(LIGHT_PIN);
}