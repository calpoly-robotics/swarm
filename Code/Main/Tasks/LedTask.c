#include "../globals.h"

void runLED();
	

void initLED()
{
	tasks[LED_TASK] = (Task) {0,0,0,10000,&runLED};
	
	// init stuff
	sbi(DDRB, 2);
}

void runLED()
{
	// run stuff
	tbi(PORTB, 2);
}