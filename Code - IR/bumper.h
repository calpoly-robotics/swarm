#include "globals.h"
#include "sense.h"

#define BUMP_PIN 3

/* Reads value from the short range IR led
 * Returns analog value representing distance to object. 
 */
u16 getBumperValue();