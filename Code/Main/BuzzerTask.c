#include "globals.h"

void runBuzzer();

void initBuzzer()
{
	// init stuff
	tasks[BUZZER_TASK] = (Task) {0,0,0,100,&runBuzzer};
}

void runBuzzer()
{
	// run stuff
}