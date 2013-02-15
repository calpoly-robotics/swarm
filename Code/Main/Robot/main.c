#include "globals.h"


void init()
{
	uartInit();		// Initialize the UART
	initClock();	// Connor's Clock init function
	initADC();
	initBattery();
	initBehavior();
	initBuzzer();
	initIR();
	initLED();
	initLightSensor();
	initMotor();
	initDistanceSensor();
}

int main()
{
	init();
	
	u08 i = 0;		// Cycles through each task
	u32 clock;

	sei();

	while (1)
	{
		uartPrint_u16(readDistanceSensor());
		uartPrintString("\r\n");
		_delay_ms(200);
   }
	
	while (1)
	{
		getTime32();
		
		// Run Task If:
		if (tasks[i].runNow) // If task has requested to be run immediately
		{
			tasks[i].runNow = 0; // Clear immediate running
			tasks[i].lastRun = time;// This is Connor's gettime32 function
			tasks[i].run(); // Runs the state machine belonging to the task
		}
		else if (time > (tasks[i].lastRun + tasks[i].interval))
		{
			tasks[i].lastRun = time; // This is Connor's gettime32 function
			tasks[i].run(); // Runs the state machine belonging to the task
		}
		
		if (++i == NUM_TASKS) // reset i after last task is checked
		{
			i = 0;
		}
	}
}
