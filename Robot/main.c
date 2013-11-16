#include "globals.h"
#include "Drivers/drivers.h"
#include "Tasks/tasks.h"
#include "Tasks/irTask.h"


void init() {
	initDrivers();
	uartPrintf("Finished driver init\n");
	uartPrintf("Adding all tasks\n");
	Task* tmp = generateTask(runIR);

}

int main() {
	init();
	uartPrintf("Init complete\n");

	u08 i = 0;
	u32 currTime;

	while (1) {
		currTime = getTime32();
		if (tasks[i] != NULL) { 

			Task task = *tasks[i];

			if (task.runNow) {
				task.runNow = 0;
				task.lastRun = currTime;
				task.run();
			} else if (currTime > (task.lastRun + task.interval)) {
				task.lastRun = currTime;
				task.run();
			}
		}

		if (++i == numTasks) {
			i = 0;
		}

	}

	return 0;
}