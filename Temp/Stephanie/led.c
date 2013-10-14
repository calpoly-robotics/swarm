#include "led.h"

void ledInit() {
   sbi(DDRB, RED_LED);
   sbi(DDRB, GREEN_LED);
}

void greenLedOn() {
   sbi(PORTB, GREEN_LED);
}

void greenLedOff() {
   cbi(PORTB, GREEN_LED);
}

void toggleGreenLed() {
   tbi(PORTB, GREEN_LED);
}

void redLedOn() {
   sbi(PORTB, RED_LED);
}

void redLedOff() {
   cbi(PORTB, RED_LED);
}

void toggleRedLed() {
   tbi(PORTB, RED_LED);
}