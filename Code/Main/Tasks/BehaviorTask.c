#include "../globals.h"

void runBehavior();


void initBehavior()
{
	tasks[BEHAVIOR_TASK] = (Task) {0,0,0,100,&runBehavior};
	
	// init stuff
}

void runBehavior()
{
	// run stuff
}