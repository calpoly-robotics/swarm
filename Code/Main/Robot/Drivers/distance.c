#include "../globals.h"

void initDistanceSensor() {
   sbi(DDRA, 6);
   cbi(PORTA, 6);
   cbi(DDRA, 7);
}

u16 readDistanceSensor() {
	sbi(PORTA, 6);
   u16 val = readADC(7);
	cbi(PORTA, 6);
	return val;
}