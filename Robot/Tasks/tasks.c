#include "tasks.h"

#define INCREASE_BY 5

volatile u08 maxTasks;

void initTasks() {
	numTasks = 0;
	maxTasks = INCREASE_BY;
	tasks = calloc(maxTasks, sizeof(Task*));
}

/**
 * returns task pointer on success or 
 */
Task* addTask(void (*runFunc)()) {
	if (numTasks == maxTasks) {
		// try to reallocate memory
		void* tmp = realloc(tasks, sizeof(Task*)*(maxTasks+INCREASE_BY));
		if (tmp == NULL) // did it fail? :(
			return NULL;

		maxTasks += INCREASE_BY;
		tasks = tmp;
	}

	Task* task = malloc(sizeof(Task));
	(*task).run = runFunc;
	(*task).index = numTasks;

	tasks[numTasks] = task;
	numTasks++;
	return task;
}

void removeTask(u08 index) {
	tasks[index] = NULL;
	if (--numTasks < maxTasks - INCREASE_BY) {
		// we should consolidate...
		int i;
		for (i = 0; i < maxTasks; i++) {
			if (tasks[i] == NULL && tasks[i+1] != NULL) {
				tasks[i] = tasks[i+1];
				tasks[i+1] = NULL;
				(*tasks[i]).index = i;
			}
		}

		void* tmp = realloc(tasks, sizeof(Task*)*(maxTasks-INCREASE_BY));
		if (tmp == NULL) // did it fail? :(
			return;

		maxTasks -= INCREASE_BY;
		tasks = tmp;

	}
}
