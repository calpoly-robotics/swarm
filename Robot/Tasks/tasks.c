#include "tasks.h"

void initTasks() {
	last = NULL;
}

/**
 * returns task pointer on success or 
 */
 Task* addTask(void (*runFunc)()) {
 	Task* newTask = (Task*)malloc(sizeof(Task));
 	//uartPrintf("%x\t%x\n",newTask,last);
 	(*newTask).run = runFunc;
 	if (last == NULL) {
 		(*newTask).prev = newTask;
 		(*newTask).next= newTask;
 	} else {
		 (*newTask).next = (*last).next;
		 (*newTask).prev = last;
 		(*(*last).next).prev = newTask;
 		(*last).next = newTask;
 	}
	 
	 last = newTask;

 	return newTask;
 }

 void removeTask(Task* toRemove) {
 	(*toRemove).prev = (*toRemove).next;
 }
// Task* addTask(void (*runFunc)()) {
// 	if (numTasks == maxTasks) {
// 		// try to reallocate memory
// 		void* tmp = realloc(tasks, sizeof(Task*)*(maxTasks+INCREASE_BY));
// 		if (tmp == NULL) // did it fail? :(
// 			return NULL;

// 		maxTasks += INCREASE_BY;
// 		tasks = tmp;
// 	}

// 	Task* task = malloc(sizeof(Task));
// 	(*task).run = runFunc;
// 	(*task).index = numTasks;

// 	tasks[numTasks] = task;
// 	numTasks++;
// 	return task;
// }

// void removeTask(u08 index) {
// 	tasks[index] = NULL;
// 	if (--numTasks < maxTasks - INCREASE_BY) {
// 		// we should consolidate...
// 		int i;
// 		for (i = 0; i < maxTasks; i++) {
// 			if (tasks[i] == NULL && tasks[i+1] != NULL) {
// 				tasks[i] = tasks[i+1];
// 				tasks[i+1] = NULL;
// 				(*tasks[i]).index = i;
// 			}
// 		}

// 		void* tmp = realloc(tasks, sizeof(Task*)*(maxTasks-INCREASE_BY));
// 		if (tmp == NULL) // did it fail? :(
// 			return;

// 		maxTasks -= INCREASE_BY;
// 		tasks = tmp;

// 	}
// }
