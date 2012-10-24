// Define Task Variables
typdef struct {
	uo8 state;
	u08 runNow;
	u08 lastRun;
	u32 interval;
	void (*run)();
} Task;
	
// #defines
#define NUM_TASKS 		5

#define BATTERY_TASK 	0
#define IR_TASK 		1
#define BUZZER_TASK 	2
#define LED_TASK 		3
#define BEHAVIOR_TASK 	4

// Array of Tasks
volatile Task tasks[NUM_TASKS];




