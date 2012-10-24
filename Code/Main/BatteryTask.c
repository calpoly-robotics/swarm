#include "globals.h"

void runBattery();


void initBattery()
{
	// init stuff
	tasks[BATTERY_TASK] = (Task) {0,0,0,100,&runBattery};
}

void runBattery()
{
	// run stuff
}