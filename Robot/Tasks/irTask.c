#include "irTask.h"
#include "../Drivers/ir.h"

u08 lastRun = 0;
Task* irTask;

void initIRTask() {
	irTask = addTask(runIR);
 	(*irTask).interval = 10;
}

void runIR() {

	if (lastRun) { // rx was last run
		manageTransmit();
		lastRun = 1;
	} else { // tx last run
		manageRecieve();
		lastRun = 0;
	}

	// TODO anything else here?
}

void txBufferFull() {
	(*irTask).runNow = 1;
}