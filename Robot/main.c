#include "globals.h"
#include "Drivers/drivers.h"
#include "Tasks/tasks.h"
#include "Tasks/irTask.h"
#include "Tasks/irTest.h"
#include "Tasks/batteryTask.h"
#include "Tasks/buzzerTask.h"
#include "Tasks/ledTask.h"
#include "Tasks/behaviorTask.h"


void init() {
	initDrivers();
	uartPrintf("Finished driver init\n");
	
	uartPrintf("Adding all tasks\n");
	initIRTask();
	initIRTestTask();
	// addTask(runBattery);
	
	// addTask(runBuzzer);
	// addTask(runBehavior);

}

int main() {
	init();
	uartPrintf("Init complete\n");

	u08 i = 0;
	u32 currTime;

	while (1) {
		currTime = getTime32();
		
		if (tasks[i] != NULL) { 

			volatile Task* task = tasks[i];

			if ((*task).runNow) {
				(*task).runNow = 0;
				(*task).lastRun = currTime;
				(*task).run();
				uartPrintDebug(5);
			} else if (currTime > ((*task).lastRun + (*task).interval)) {
				(*task).lastRun = currTime;
				(*task).run();
			}
			// uartPrintf("lastRun:%.6lu\tcurrTime:%.6lu\tbullshit:%.6lu\n",(*task).lastRun,currTime,bullshit);
			// uartPrintf("int+lastRun:%.6lu\tcurrTime:%.6lu\n",(*task).lastRun+10000,currTime);
			// uartPrintf("(*task):%u\t%.6lu ticks left\t currTime:%.6lu\tlastRun:%.6lu\n",i,((*task).lastRun+(*task).interval - currTime),currTime,(*task).lastRun);
		}

		if (++i == numTasks) {
			i = 0;
		}

	}

	return 0;
}