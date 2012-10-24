#include "globals.h"

void runBehavior();


void initBehavior()
{
	// init stuff
	tasks[BEHAVIOR_TASK] = (Task) {0,0,0,100,&runBehavior};
}

void runBehavior()
{
	// run stuff
}