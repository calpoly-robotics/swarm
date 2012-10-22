#include "globals.h"
#include "sense.h"

#define DIST_PIN 7
#define DIST_ENABLE 6


/* Do pullups need to be set for this?
 */
void distanceInit();

/* Enables the distance IR led
 */
void distanceOn();

/* Disables the distance IR led
 */
void distanceOff();

/* Reads value from the distance IR led
 * Returns analog value representing distance to object. 
 */
u16 getDistance();