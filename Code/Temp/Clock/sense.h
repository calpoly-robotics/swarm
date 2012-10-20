
/* Initializes the board LEDs as outputs.
 */
void senseInit();

/* Gets the value of the specified LED.
 * pin = integer 0-7
 * returns 16 bit value from the LED
 */
u16 readSensorValue(u08 pin);