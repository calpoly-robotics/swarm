#include "globals.h"
#include "sense.h"

// init - set 00 s1/s0 (23.9.1)
void senseInit()
{
   //ADMUX &= 0x3F;
   sbi(ADMUX, 7);
   sbi(ADMUX, 6);
   
   //enable 
   sbi(ADCSRA, 7);
   //set prescaler to 16
   sbi(ADCSRA, 0);
   sbi(ADCSRA, 2);
}

/* PIN MUST BE 0-7
 * 
 * read - take in pin number -> set admux 2:0
 * set bit 6 adcsra (23.9.2)
 * return adch/adcl (23.9.3)
 */
u16 readSensorValue(u08 pin) 
{
   u16 i = 0;
   
   //clear and write the pin number to register
   cbi(ADMUX, 0);
   cbi(ADMUX, 1);
   cbi(ADMUX, 2);
   ADMUX |= (pin & 0x07);
   
   //set bit 6 to enable start conversion
   sbi(ADCSRA, 6);
   
   //loop until bit 6 returns to 0
   while ((ADCSRA & 0x40) != 0); 
   
   //return the value of the bin
   return ADC;
}
