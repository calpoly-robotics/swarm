#include "globals.h"
#include <util/parity.h>

inline void enableOCR(u08 val)
{
	TCNT2 = 0x00;
	OCR2A = val;
	sbi(TIFR2, 1); // prevent immediate interrupt
	TIMSK2 = 0x02; // turn on OCR1A interrupt
}

inline void disableOCR()
{
	TIMSK2 = 0x00; // turn off OCR1A interrupt
}

void enablePCINT()
{
	PCICR = 0x08;
	PCMSK3 = 0x02;
}

void disablePCINT()
{
	PCICR = 0x00;
	PCMSK3 = 0x00;
}

// timer interrupt
ISR(TIMER2_COMPA_vect)
{
	cbi(PORTD, 0);
	disableOCR();
}

ISR(PCINT3_vect)
{
	if (gbi(PIND, 1))
		return;
	
	
	sbi(PORTD, 0);
	enableOCR(19);
	// if (!gbi(PIND, 1))
	// {
		// tbi(PORTB, 0);
	// }
}

void init()
{
	// TCCR2A = 0x02; // CTC mode
	// TCCR2B = 0x03; // CTC mode and clk/32 prescaler
	// TIMSK2 = 0x00; // turn off OCR2A interrupt
	
	// cbi(DDRD, 1); // set PD1 as input
	// sbi(PORTD, 1); // turn on pull-up
	
	// sbi(DDRD, 0); // RX pin as output for debug
	// cbi(PORTD, 0);
	
	// enablePCINT();
	// sei();
	
	uartInit();		// Initialize the UART
	// initClock();	// Connor's Clock init function
	initADC();
	// initBehavior();
	// initBuzzer();
	// initIR();
	initLED();
}

int main()
{
	init();
	u08 i = 0;		// Cycles through each task
	u32 clock;

	//sei();

	while (1)
	{
		uartPrint_u16(readADC(CURRENT_SENSE));
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
