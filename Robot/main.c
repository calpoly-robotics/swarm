#include "globals.h"
#include "Drivers/drivers.h"
#include "Tasks/tasks.h"
#include "Tasks/irTask.h"
#include "Tasks/batteryTask.h"
#include "Tasks/buzzerTask.h"
#include "Tasks/ledTask.h"
#include "Tasks/behaviorTask.h"

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

void init() {
	// initDrivers();
	uartInit();
	initMotor();

	uartPrintf("Finished driver init\n");
	
	uartPrintf("Adding all tasks\n");
	// initIRTask();
	// addTask(runBattery);
	
	// addTask(runBuzzer);
	// addTask(runBehavior);

}

int main() {
	init();
	// uartPrintf("Init complete\n");

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

	/*
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
	*/

	while(1) {
		shutdownMotor();
		_delay_ms(1000);
		initMotor();
		leftMotor(-255);
		rightMotor(255);
		_delay_ms(1000);
	}

	return 0;
}