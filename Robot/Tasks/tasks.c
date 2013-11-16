#include "tasks.h"

#define INCREASE_BY 5

volatile u08 maxTasks = numTasks + INCREASE_BY;

void initTasks() {
	tasks = calloc(maxTasks, sizeof(Task*));
}

/**
 * returns non-zero on success
 */
u08 addTask(Task* task) {
	if (numTasks == maxTasks) {
		// try to reallocate memory
		void* tmp = realloc(tasks, sizeof(Tasks*)*(maxTasks+INCREASE_BY));
		if (tmp == NULL) // did it fail? :(
			return NULL;

		maxTasks += INCREASE_BY;
		tasks = tmp;
	}

	
	tasks[numTasks] = task;
	numTasks++;
}

void removeTask(u08 index) {
	tasks[index] = NULL;
}