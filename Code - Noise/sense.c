
// init - set 00 s1/s0 (23.9.1)
void senseInit()
{
   ADMUX &= 0x3F;
}

/* PIN MUST BE 0-7
 * 
 * read - take in pin number -> set admux 2:0
 * set bit 6 adcsra (23.9.2)
 * return adch/adcl (23.9.3)
 */
u16 readSensorValue(u08 pin) 
{
   ADMUX &= 0xF8;
   ADMUX |= (pin & 0x07)
   
   ADSCRA |= 0x40;
   
   return (ADCH << 8) | ADCL;
}
