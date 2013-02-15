#include "../globals.h"

void runIR();


void initIR()
{
	tasks[IR_TASK] = (Task) {0,0,0,10,&runIR};
	
	// init stuff
}

void runIR()
{
	// run stuff
}