#include "batteryTask.h"
#include "../pins.h"
#include "../Drivers/adc.h"

#define ADC_MAX_VAL ((1<<11) - 1)

// to adjust for voltage divider
// pin voltage / (18/(18+7.5)) = battery voltage

void initBatteryTask() {
	
}

void runBattery() {
	u16 volts = readADC(BATTERY_SENSE); // adjust for voltage divider
	if (volts < )

}