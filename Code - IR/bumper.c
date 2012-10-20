#include "bumper.h"

u16 getBumperValue() {
   return readSensorValue(BUMP_PIN);
}