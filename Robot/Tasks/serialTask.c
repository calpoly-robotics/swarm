#include "serialTask.h"
#include "../Drivers/serial.h"

Task* serialTask;

void initSerialTask() {
	serialTask = addTask(runSerial);
 	(*serialTask).interval = 100;
}

void runSerial() {
	driverRunSerial();
}