#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "adc.h"
#include "../globals.h"
#include <util/delay.h>

void initDistanceSensor();

u16 readDistanceSensor();

void shutdownDistanceSensor();

#endif /*DISTANCE_H_*/