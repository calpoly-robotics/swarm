#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "tasks.h"

void initLEDTask();

void runLed();

void turnOnLED(u08 which, u16 duration);

#endif 