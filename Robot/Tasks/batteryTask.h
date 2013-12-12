#ifndef BATTERY_TASK_H_
#define BATTERY_TASK_H_

#include "tasks.h"

// millivolts
#define WARNING_VOLTAGE 	3600
#define CRITICAL_VOLTAGE	3400

void initBatterTask();

void runBattery();

#endif 