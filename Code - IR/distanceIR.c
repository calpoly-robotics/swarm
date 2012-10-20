#include "distanceIR.h"

u16 getDistanceIRValue() {
   return readSensorValue(DIST_IR_PIN);
}