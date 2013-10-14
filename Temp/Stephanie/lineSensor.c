#include "lineSensor.h"

u16 getLineSensorValue1() {
   return readSensorValue(LN_SENSOR_PIN1);
}

u16 getLineSensorValue2() {
   return readSensorValue(LN_SENSOR_PIN2);
}