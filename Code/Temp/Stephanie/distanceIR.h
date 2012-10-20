#include "globals.h"
#include "sense.h"

#define DIST_IR_PIN 7

/* Reads value from the distance IR led
 * Returns analog value representing distance to object. 
 */
u16 getDistanceIRValue();