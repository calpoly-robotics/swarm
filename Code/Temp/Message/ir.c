#include "ir.h"
#include <util/parity.h>
#include <stdlib.h>

#define IR_BUFFER_SIZE 8
#define IR_START_LEN 2
#define IR_OCR_VAL 199

volatile u08 irTransmitBuffer[IR_BUFFER_SIZE][MAX_MESSAGESIZE];
volatile u08 irTransmitStart = 0;
volatile u08 irTransmitEnd = 0;
volatile u08 irCurrentMsg[MAX_MESSAGESIZE];
volatile u08 irTransmitIndex;

volatile u16 testBuffer[50];
volatile u08 testIndex = 0;

#if (IS_RECEIVER == 1)
void doTest()
{
	if (testIndex > 0)
	{
		int i;
		for (i = 0; i < testIndex; i++)
		{
			uartPrint_u08(((testBuffer[i]/20) - 11) & 0xFF);
			uartPrintChar(' ');
			_delay_ms(5);
		}
		uartPrintChar('\r');
		uartPrintChar('\n');
		testIndex = 0;
	}
}
#endif

// initializes the IR transmitting (and eventually receiving)
void initIR()
{
#if (IS_RECEIVER == 0)
	TCCR1A = 0x00; // CTC mode
	TCCR1B = 0x09; // CTC mode and clk/1 prescalar
	TCCR1C = 0x00;
	OCR1A = IR_OCR_VAL; // interrupt every IR_OCR_VAL counts
	TIMSK1 = 0x00; // turn off interrupts
#endif
	
#if (IS_RECEIVER == 1)
	TCCR1A = 0x00; // CTC mode
	TCCR1B = 0x09; // CTC mode and clk/1 prescalar
	TCCR1C = 0x00;
	OCR1A = 50000; // interrupt every 10000 counts
	TCNT1 = 0x00;
	TIMSK1 = 0x02; // turn on OCR1A interrupt
	
	PCICR = 0x01;
	PCMSK0 = 0x08;
#endif
	sei();
}

/* Takes an array of bytes and calculates the 4 bit checksum. Will work for
	bytes where both nibbles contain data or just lower nibble contains data
	(assuming upper nibble is cleared). */
u08 checksum4(u08 *data; u08 len)
{
	u08 result = 0;
	for (i = 0; i < len; i++)
	{
		result ^= (data[i] >> 4) ^ (data[i] & 0x0F);
	}
	
	return result;
}

void sendMessage(Message msg)
{
}

/*
 * If there's something in the message buffer and we aren't currently transmitting,
 * expand it and put it into the transmit buffer.
 */
void manageTransmit()
{

}

#if (IS_RECEIVER == 0)
// ISR for transmitting (and eventually receiving)
ISR(TIMER1_COMPA_vect)
{
	if (irCurrentMsg[irTransmitIndex] > 1)
	{
		TIMSK1 = 0x00; // turn off OCR1A interrupt
		cbi(PORTA, 1);
		return;
	}
	
	if (irCurrentMsg[irTransmitIndex] == 0)
		cbi(IR_LED_PORT, IR_LED_PIN);
	else if (irCurrentMsg[irTransmitIndex] == 1)
		sbi(IR_LED_PORT, IR_LED_PIN);
	
	irTransmitIndex++;
}
#endif

#if (IS_RECEIVER == 1)
// ISR for transmitting (and eventually receiving)
ISR(TIMER1_COMPA_vect)
{
}

ISR(PCINT0_vect)
{
	if (!gbi(PINA, 3))
	{
		return;
	}
	
	testBuffer[testIndex++] = TCNT1;
	TCNT1 = 0;
}
#endif
