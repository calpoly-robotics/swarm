#include "globals.h"

void runIR();


void initIR()
{
	// init stuff
	tasks[IR_TASK] = (Task) {0,0,0,10,&runIR};
}

void runIR()
{
	// run stuff
}