#include "charger.h"

u16 getChargerValue() {
   return readSensorValue(CHARGER_PIN);
}