#include "batteryTask.h"
#include "../pins.h"
#include "../Drivers/adc.h"
#include <avr/sleep.h>

#define ADC_MAX_VAL (1024)


#define VOLTS_TO_10BIT(__volts) ((u16)(__volts*(18/(18+7.5)/3*1024)))

// to adjust for voltage divider
// pin voltage / (18/(18+7.5)) = battery voltage

volatile Task* task;

void initBatteryTask() {
	task = addTask(runBattery);
 	(*task).interval = 40000; // about once every 5 seconds.
}

void batteryCritical() {
	// engage power-down. Will be woken only by TWI address match

}

void batteryWarning() {
	// engage power-save. Will be woken on TIMER2_OVF
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sleep_mode();

	// do the check again.
	runBattery();
}

void runBattery() {
	u16 volts = readADC(BATTERY_SENSE); // adjust for voltage divider
	if (volts < VOLTS_TO_10BIT(3.4)) {
		batteryCritical();
	} else if (volts < VOLTS_TO_10BIT(3.6)) { 
		batteryWarning();
	}

}

ISR(TIMER2_OVF_vect) {
	// TODO: broadcast help signal.

}