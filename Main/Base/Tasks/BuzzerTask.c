#include "../globals.h"

void runBuzzer();

void initBuzzer()
{
	tasks[BUZZER_TASK] = (Task) {0,0,0,100,&runBuzzer};
	
	// init stuff
}

void runBuzzer()
{
	// run stuff
}