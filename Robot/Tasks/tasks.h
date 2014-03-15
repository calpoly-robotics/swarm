#ifndef TASKS_H_
#define TASKS_H_ 1

#include "../globals.h"

typedef struct Task {
	u08 index;
	u08 state;
	u08 runNow;
	u32 lastRun;
	u32 interval;
	void (*run)();
	struct Task* next;
	struct Task* prev;
} Task;

Task* last;

void initTasks();
Task* addTask(void(*runFunc)());;
void removeTask(Task*);

#endif