#include "../globals.h"

void runBattery();


void initBattery()
{
	tasks[BATTERY_TASK] = (Task) {0,0,0,100,&runBattery};
	
	// init stuff
}

void runBattery()
{
	// run stuff
}