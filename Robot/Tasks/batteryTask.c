#include "batteryTask.h"
#include "../pins.h"
#include "../Drivers/adc.h"

void initBatteryTask() {
	
}

void runBattery() {
	u16 volts = readADC(BATTERY_SENSE);
}