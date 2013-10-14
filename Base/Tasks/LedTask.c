#include "../globals.h"

#define RED_LED 3
#define GREEN_LED 2
#define BLUE_LED 1

void runLED();

void initLED()
{
	tasks[LED_TASK] = (Task) {0,0,0,10000,&runLED};
	
	// init stuff
	sbi(DDRB, RED_LED);
   sbi(PORTB, RED_LED);
	sbi(DDRB, GREEN_LED);
   sbi(PORTB, GREEN_LED);
	sbi(DDRB, BLUE_LED);
   sbi(PORTB, BLUE_LED);
}

void runLED()
{
}