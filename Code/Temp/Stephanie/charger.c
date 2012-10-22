#include "charger.h"

u16 getVoltage() {
   return readSensorValue(CHARGER_PIN);
}