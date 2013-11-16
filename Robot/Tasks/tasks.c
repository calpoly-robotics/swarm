#include "tasks.h"

#define INCREASE_BY 5

volatile u08 maxTasks;

void initTasks() {
	numTasks = 0;
	maxTasks = INCREASE_BY;
	tasks = calloc(maxTasks, sizeof(Task*));
}

/**
 * returns non-zero on success
 */
u08 addTask(Task* task) {
	if (numTasks == maxTasks) {
		// try to reallocate memory
		void* tmp = realloc(tasks, sizeof(Task*)*(maxTasks+INCREASE_BY));
		if (tmp == NULL) // did it fail? :(
			return 0;

		maxTasks += INCREASE_BY;
		tasks = tmp;
	}


	tasks[numTasks] = task;
	numTasks++;
	return 1;
}

void removeTask(u08 index) {
	tasks[index] = NULL;
}

Task* generateTask(void (*runFunc)()) {
	Task* tmp = malloc(sizeof(Task));


	return tmp;
}
