// Define Task Variables
typdef struct {
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

// Initialze Task Variables
tasks[BATTERYTASK] = 	(0,0,100,&runBattery);
tasks[IR_TASK] = 		(0,0,10,&runIR);
tasks[BUZZER_TASK] = 	(0,0,100,&runBuzzer);
tasks[LED_TASK] = 		(0,0,100,&runLed);
tasks[BEHAVIOR_TASK] = 	(0,0,100,&runBehavior);


