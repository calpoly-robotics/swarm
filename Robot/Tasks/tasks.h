#ifndef TASKS_H_
#define TASKS_H_

#include "../globals.h"

typedef struct {
	u08 index;
	u08 state;
	u08 runNow;
	u32 lastRun;
	u32 interval;
	void (*run)();
} Task;

volatile u08 numTasks;

volatile Task** tasks; // array of task pointers

void initTasks();
Task* addTask(void(*runFunc)());;
void removeTask(u08 index);

#endif