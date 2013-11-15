#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "clock.h"
#include "motor.h"
#include "lightSensor.h"
#include "adc.h"
#include "distance.h"
#include "serial.h"

/**
 * Wrapper for all the init functions for the various drivers
 */
inline void initDrivers() {
	uartInit();
	initClock();
	initMotor();
	initLightSensor();
	initADC();
	initDistanceSensor();
}

#endif /* DRIVERS_H_*/