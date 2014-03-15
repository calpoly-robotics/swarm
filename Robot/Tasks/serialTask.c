#include "serialTask.h"
#include "../Drivers/serial.h"

Task* serialTask;

void initSerialTask() {
	serialTask = addTask(runSerial);
 	(*serialTask).interval = 100;
}

void runSerial() {
	// sbi(PINA,1);
	// sbi(PINB,2);
	driverRunSerial();
}