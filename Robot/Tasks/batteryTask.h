#ifndef BATTERY_TASK_H_
#define BATTERY_TASK_H_

#include "tasks.h"

// millivolts
#define WARNING_VOLTAGE 	3600
#define CRITICAL_VOLTAGE	3400

#define VOLTS_TO_10BIT(__volts) ((u16)(__volts*(18.0/(18.0+7.5)/3.0*1024.0)))
#define BITS_TO_VOLTS(__bits) ((double)(__bits/(18.0/(18.0+7.5)/3.0*1024.0)))

void initBatterTask();

void runBattery();

#endif 