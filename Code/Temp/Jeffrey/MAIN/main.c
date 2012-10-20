#include "globals.h"
// #include "BatteryTask.h"
// #include "IRTask.h"
// #include "BuzzerTask.h"
// #include "LedTask.h"
// #include "BehaviorTask.h"



void init()
{

}

int main()
{
	uartInit();		// Initialize the UART
	ClockInit();	// Connor's Clock init function
	
	u08 i = 0;		// Cycles through each task
	
	while (1)
	{
	
		// Run Task If:
		if (tasks[i].runNow == 1) // If task has requested to be run immediately
			{
				tasks[i].lastRun = getTime32(); // This needs Connor's gettime32 function
				tasks[i].run(); //Runs the state machine belonging to the task
			}
		else if (getTime32() > (tasks[i].lastRun + tasks[i].interval))
			{
				tasks[i].lastRun = getTime32(); // This needs Connor's gettime32 function
				tasks[i].run(); //Runs the state machine belonging to the task
			}
	
		i++; // Increment to next task
		
		if (i > NUM_TASKS) //reset i after last task is checked
		{
			i = 0;
		}
	
	
	
	}
}
