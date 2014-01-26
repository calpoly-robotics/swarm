#include "batteryTask.h"
#include "../pins.h"
#include "../Drivers/adc.h"
#include <avr/sleep.h>

#define ADC_MAX_VAL (1024)


#define VOLTS_TO_10BIT(__volts) ((u16)(__volts*(18/(18+7.5)/3*1024)))

// to adjust for voltage divider
// pin voltage / (18/(18+7.5)) = battery voltage

volatile Task* task;
volatile u16 timeRested = 0; // # of ~8 sec intervals

void initBatteryTask() {
	task = addTask(runBattery);
 	(*task).interval = 40000; // about once every 5 seconds.

 	// Enable the overflow interrupt
	sbi(TIMSK2, TOIE2);
}

void setupPowerSave() {
	// turn off power-sucking things


	// start timer
	// Set prescaller to 1/1024 (~8kHz)
	sbi(TCCR2B, CS20);
	sbi(TCCR2B, CS22);
}

void endPowerSave() {
	// turn on the power-sucking things


	// stop timer
	cbi(TCCR2B, CS20);
	cbi(TCCR2B, CS22);
}

void batteryCritical() {
	// engage power-down. Will be woken only by TWI address match
	setupPowerSave();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();
	endPowerSave();
}

void batteryWarning() {
	static u08 numIterations;
	// engage power-save. Will be woken on TIMER2_OVF

	setupPowerSave();

	do {
		set_sleep_mode(SLEEP_MODE_PWR_SAVE);
		sleep_mode();
	} while((timeRested%numIterations)!=0);

	endPowerSave();
}

void runBattery() {
	do {
		u16 volts = readADC(BATTERY_SENSE); // adjust for voltage divider
		if (volts < VOLTS_TO_10BIT(3.4)) {
			batteryCritical();
		} else if (volts < VOLTS_TO_10BIT(3.6)) { 
			batteryWarning();
		} else {
			// battery level was good. let's
			return;
		}

		// battery was low and we have resumed up to here
		// do another check.
	} while(1);
}

ISR(TIMER2_OVF_vect) {
	timeRested++;
}
