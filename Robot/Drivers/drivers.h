#ifndef DRIVERS_H_
#define DRIVERS_H_ 1

#include "clock.h"
#include "motor.h"
#include "lightSensor.h"
#include "adc.h"
#include "distance.h"
#include "serial.h"
#include "ir.h"

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
#ifdef BUZZER
	initBuzzer();
#else
	initIR();
#endif
}

void shutdownDrivers() {
	shutdownMotor();
}

#endif /* DRIVERS_H_*/