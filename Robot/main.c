#include "globals.h"
#include "Drivers/drivers.h"
#include "Tasks/tasks.h"
#include "Tasks/irTask.h"
#include "Tasks/irTest.h"
#include "Tasks/batteryTask.h"
#include "Tasks/buzzerTask.h"
#include "Tasks/ledTask.h"
#include "Tasks/behaviorTask.h"
#include <util/delay.h>


void init() {
	initTasks();
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
	sbi(DDRA,PINA1);
	sbi(DDRB, 2);
	sbi(DDRB, 3);
	sbi(PORTB, 2);
	sbi(PORTB, 3);

	init();
	uartPrintf("Init complete\n");
	uartPrintString("*************************************************\n");

	u32 currTime;

	// while(1) {
	// 	sbi(PORTC, TRANSMIT_PIN);
	// }

	Task* task = last;

	while (1) {
		currTime = getTime32();
		sbi(PINB, 2);
		
		// if (tasks[i] != NULL) { 

		// 	volatile Task* task = tasks[i];

		if ((*task).runNow) {
			(*task).runNow = 0;
			(*task).lastRun = currTime;
			(*task).run();
			// uartPrintDebug(5);
		} else if (currTime > ((*task).lastRun + (*task).interval)) {
			(*task).lastRun = currTime;
			(*task).run();
		}

		task = (*task).next;
		// _delay_ms(1000);
		// 	// uartPrintf("lastRun:%.6lu\tcurrTime:%.6lu\tbullshit:%.6lu\n",(*task).lastRun,currTime,bullshit);
		// 	// uartPrintf("int+lastRun:%.6lu\tcurrTime:%.6lu\n",(*task).lastRun+10000,currTime);
		// 	// uartPrintf("(*task):%u\t%.6lu ticks left\t currTime:%.6lu\tlastRun:%.6lu\n",i,((*task).lastRun+(*task).interval - currTime),currTime,(*task).lastRun);
		// }

		// if (++i == numTasks) {
		// 	i = 0;
		// }

	}

	return 0;
}