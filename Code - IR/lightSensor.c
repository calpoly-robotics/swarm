#include "lightSensor.h"

u16 getLightSensorValue() {
   return readSensorValue(LIGHT_SENSOR_PIN);
}