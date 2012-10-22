#include "globals.h"
#include "sense.h"

#define FRONT_PIN 3
#define LEFT_PIN 2
#define RIGHT_PIN 1
#define SHORT_ENABLE 4

/* Initializes board for using short range IR
 */
void shortInit();

/* Enables the short range IR
 */
void shortOn();

/* Disables the short range IR
 */
void shortOff();

/* Reads value from left line sensor
 * Returns analog value representing color of floor
 */
u16 getLeftShort();

/* Reads value from right line sensor
 * Returns analog value representing color of floor
 */
u16 getRightShort();

/* Reads value from the short range IR led
 * Returns analog value representing distance to object. 
 */
u16 getFrontValue();

