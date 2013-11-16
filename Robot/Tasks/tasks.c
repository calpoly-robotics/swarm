#include "tasks.h"

void initTasks() {
	tasks = calloc(numTasks, sizeof(Task*));
}

void addTask(Task* task) {

}

void removeTask(u08 index) {
	tasks[index] = NULL;
}