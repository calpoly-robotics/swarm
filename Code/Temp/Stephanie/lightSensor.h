#include "globals.h"
#include "sense.h"

#define LIGHT_PIN 5

/* Initialize light sensor as input.
 */
void lightInit();

/* Reads the value from the light sensor on top of SWARM bots.
 * Returns 16 bit analog value 
 */
u16 getLightSensorValue();