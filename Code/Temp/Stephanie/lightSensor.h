#include "globals.h"
#include "sense.h"

#define LIGHT_SENSOR_PIN 5

/* Reads the value from the light sensor on top of SWARM bots.
 * Returns 16 bit analog value 
 */
u16 getLightSensorValue();