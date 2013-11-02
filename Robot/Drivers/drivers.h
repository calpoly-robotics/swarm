#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "clock.h"

/**
 * Wrapper for all the init functions for the various drivers
 */
inline void initDrivers() {
	initClock();
}

#endif /* DRIVERS_H_*/