#include "ledTask.h"
#include "../pins.h"

#ifdef PORTE

Task* myTask;

u08 onTime;
u08 offTime;
volatile u08 counter;
volatile u08 state;

void initLEDTask() {
	sbi(DDRE, RED_LED);
	sbi(DDRE, GREEN_LED);
	sbi(DDRE, BLUE_LED);

	// fast pwm
	sbi(TCCR5A, WGM50);
	sbi(TCCR5A, WGM51);
	sbi(TCCR5B, WGM52);
	sbi(TCCR5B, WGM53);

	// clear pin on oc match
	sbi(TCCR5A, COM5A1);
	sbi(TCCR5A, COM5B1);
	sbi(TCCR5A, COM5C1);

	sbi(TIMSK5, TOIE5);

	myTask = addTask(runLed);
	(*myTask).interval = 256;
}

void runLed() {

}

void blink(u08 on, u08 off, u16 red, u16 green, u16 blue) {
	onTime = on;
	offTime = off;
	counter = onTime;
	state = 1;
	OCR5A = red;
	OCR5B = green;
	OCR5C = blue;
}

void redLED(u16 intensity) {
	OCR5A = intensity;
	onTime = 0;
	offTime = 0;
}

void greenLED(u16 intensity) {
	OCR5B = intensity;
	onTime = 0;
	offTime = 0;
}

void blueLED(u16 intensity) {
	OCR5C = intensity;
	onTime = 0;
	offTime = 0;
}

ISR(TIMER5_OVF_vect) {
	if (state) {
		sbi(PORTE, RED_LED);
		sbi(PORTE, GREEN_LED);
		sbi(PORTE, BLUE_LED);
	}

	if (-- counter == 0) {
		if (state) {
			state = 0;
			counter = offTime;
		} else {
			state = 1;
			counter = onTime;
		}
	}
}

#endif