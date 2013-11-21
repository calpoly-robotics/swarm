#include "ledTask.h"
#include "../pins.h"

Task* myTask;

void initLEDTask() {
	myTask = addTask(runLed);
	sbi(DDRB, LED1);
	sbi(DDRB, LED2);
}

void runLed() {

}

void turnOnLED(u08 which, u16 duration) {
	
}