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

volatile u08 numTasks = 0;

volatile Task** tasks; // array of task pointers

void initTasks();
void addTask(Task* task);
void removeTask(u08 index);

#endif