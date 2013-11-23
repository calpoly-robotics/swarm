#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "tasks.h"
#ifdef PORTE // quick way to tell if on new chip

void initLEDTask();

void runLed();

void blink(u08 on, u08 off, u16 red, u16 green, u16 blue);

void redLED(u16 intensity);
void blueLED(u16 intensity);
void greenLED(u16 intensity);

#endif /* PORTE */
#endif /* LED_TASK_H_ */