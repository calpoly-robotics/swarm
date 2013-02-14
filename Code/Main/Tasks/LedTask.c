#include "../globals.h"

void runLED();
	

void initLED()
{
	tasks[LED_TASK] = (Task) {0,0,0,10000,&runLED};
	
	// init stuff
	sbi(DDRB, 6); // RED
	sbi(DDRB, 3); // GREEN
	sbi(DDRB, 2); // BLUE
   sbi(PORTB, 6);
   sbi(PORTB, 3);
   sbi(PORTB, 2);
}

void runLED()
{
   tbi(PORTB, 6);
   tbi(PORTB, 3);
   tbi(PORTB, 2);
   if (tasks[LED_TASK].interval == 1000)
   {
      tasks[LED_TASK].interval = 9000;
   }
   else
   {
      tasks[LED_TASK].interval = 1000;
   }
}