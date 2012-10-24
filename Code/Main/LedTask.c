#include "globals.h"

void runLED();
	

void initLED()
{
	// init stuff
	tasks[LED_TASK] = (Task) {0,0,0,100,&runLED};
}

void runLED()
{
	// run stuff
}