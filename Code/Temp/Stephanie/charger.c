#include "charger.h"

void chargetInit() {
   cbi(DDRA, CHARGER_PIN);
   cbi(DDRB, DETECT_PIN);
   cbi(DDRB, STATUS_PIN);
   
   cbi(PORTA, CHARGER_PIN);
   sbi(PORTB, DETECT_PIN);
   sbi(PORTB, STATUS_PIN);
}

u16 getVoltage() {
   return readSensorValue(CHARGER_PIN);
}