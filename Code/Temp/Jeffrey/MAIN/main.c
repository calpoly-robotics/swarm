#include "globals.h"


void init()
{

}

int main()
{
	uartInit();		// Initialize the UART
	clockInit();	// Connor's Clock init function
	
	// Initialze Task Variables
	tasks[BATTERYTASK] = 	(0,0,0,100,&runBattery);
	tasks[IR_TASK] = 		(0,0,0,10,&runIR);
	tasks[BUZZER_TASK] = 	(0,0,0,100,&runBuzzer);
	tasks[LED_TASK] = 		(0,0,0,100,&runLed);
	tasks[BEHAVIOR_TASK] = 	(0,0,0,100,&runBehavior);
	
	u08 i = 0;		// Cycles through each task
	
	while (1)
	{
	
		// Run Task If:
		if (tasks[i].runNow) // If task has requested to be run immediately
			{
				tasks[i].runNow = 0; // Clear immediate running
				tasks[i].lastRun = getTime32(); // This needs Connor's gettime32 function
				tasks[i].run(); // Runs the state machine belonging to the task
			}
		else if (getTime32() > (tasks[i].lastRun + tasks[i].interval))
			{
				tasks[i].lastRun = getTime32(); // This needs Connor's gettime32 function
				tasks[i].run(); // Runs the state machine belonging to the task
			}
	
		i++; // Increment to next task
		
		if (i == NUM_TASKS) // reset i after last task is checked
		{
			i = 0;
		}
	
	
	
	}
}
