#include "bumper.h"

void shortInit() {
   sbi(DDRA, FRONT_PIN);
   sbi(DDRA, LEFT_PIN);
   sbi(DDRA, RIGHT_PIN);
   sbi(MCUCR, 4);
}

void shortOn() {
   sbi(DDRA, SHORT_ENABLE);
}

void shortOff() {
   cbi(DDRA, SHORT_ENABLE);
}

u16 getLeftShort() {
   return readSensorValue(LEFT_PIN);
}

u16 getRightShort() {
   return readSensorValue(RIGHT_PIN);
}

u16 getBumperValue() {
   return readSensorValue(BUMP_PIN);
}