
#include "led.h"

int main()
{
   ledInit();
   
   while (1) {
       redLedOn();
	   _delay_ms(500);
	   redLedOff();
	   _delay_ms(500);
   }
   
   return 0;
}
