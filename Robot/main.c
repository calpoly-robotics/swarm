#include "globals.h"
#include "Drivers/drivers.h"
#include "Tasks/tasks.h"
#include "Tasks/irTask.h"
#include "Tasks/batteryTask.h"
#include "Tasks/buzzerTask.h"
#include "Tasks/ledTask.h"
#include "Tasks/behaviorTask.h"


void init() {
	initDrivers();
	uartPrintf("Finished driver init\n");
	
	uartPrintf("Adding all tasks\n");
	initIRTask();
	addTask(runBattery);
	
	addTask(runBuzzer);
	addTask(runBehavior);

}

int main() {
	init();
	uartPrintf("Init complete\n");

	u08 i = 0;
	u32 currTime;
	u08 tmpStr[64];
	u08 index = 0;
	while(1) {
		// uartPrintDebug(3);
		// _delay_ms(250);

		// block until data is ready
		do {
			while (!uartDataReady());
			tmpStr[index] = uartRead();
		} while (tmpStr[index++]!='\n');
		tmpStr[index] = 0; // null terminate string

		uartPrintString(tmpStr);
	}


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