#include "irTask.h"
#include "../Drivers/ir.h"

u08 irManageLastRun = 0;
Task* irTask;

void initIRTask() {
	irTask = addTask(runIR);
 	(*irTask).interval = 10;
}

void runIR() {
	// sbi(PINB,3);

	if (irManageLastRun) { // rx was last run
		manageTransmit();
		irManageLastRun = 0;
	} else { // tx last run
		manageRecieve();
		irManageLastRun = 1;
	}

	// TODO anything else here?
}

void txBufferFull() {
	(*irTask).runNow = 1;
}