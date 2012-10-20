#include "globals.h"
#include "sense.h"

void init()
{
   sbi(DDRB, 2); // red LED out as output
}

int main()
{
   int i = 0;
   u08 buf[3] = {'\n', '\r', '\0'};
   init();
   uartInit();
   senseInit();
   
   
   while (1) {
       u16 val = readSensorValue(5);
	   
	   uartPrint_u16(val);	   
	   uartPrintString(buf);

	   _delay_ms(500);
   }
   
   return 0;
}
