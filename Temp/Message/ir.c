#include "ir.h"
#include <util/parity.h>
#include <stdlib.h>

volatile Message sendMsgBuf[BUFFER_SIZE];
volatile u08 sendBufCount = 0;
volatile u08 sendBufStart = 0;
volatile u08 sendBufEnd = 0;

volatile u08 sendSequence = 0;
volatile u08 sendWidthIndex = 0;
volatile u16 sendWidths[NUM_NIBBLES+1];

volatile s08 recvWidthIndex = -1;
volatile u16 recvWidths[NUM_NIBBLES+1];

void enablePCINT();

// initializes the IR transmitting (and eventually receiving)
void initIR()
{
	TCCR1A = 0x00; // CTC mode
	TCCR1B = 0x09; // CTC mode and clk/1 prescaler
	TCCR1C = 0x00;
	TIMSK1 = 0x00; // turn on OCR1A interrupt
	sei();
	TRANSMIT_OUTPUT();
	RECEIVE_INPUT();
	enablePCINT();
	sbi(DDRB, 4);
	sbi(DDRA, 2);
}

inline void enableOCR(u16 val)
{
	TCNT1 = 0x00;
	OCR1A = val;
	sbi(TIFR1, 1); // prevent immediate interrupt
	TIMSK1 = 0x02; // turn on OCR1A interrupt
}

inline void disableOCR()
{
	TIMSK1 = 0x00; // turn off OCR1A interrupt
}

void enablePCINT()
{
	PCICR = 0x01;
	PCMSK0 = 0x08;
}

void disablePCINT()
{
	PCICR = 0x00;
	PCMSK0 = 0x00;
}

u08 isMessageIRBusy()
{
	return TIMSK1;
}

/* Takes an array of bytes and calculates the 4 bit checksum. Will work for
	bytes where both nibbles contain data or just lower nibble contains data
	(assuming upper nibble is cleared). */
u08 checksum4(u08 *data, u08 len)
{
	u08 i, result = 0;
	for (i = 0; i < len; i++)
	{
		result ^= (data[i] >> 4) ^ (data[i] & 0x0F);
	}
	
	return result;
}


void sendMessage(u08 hop, msg_type msg, u08 data)
{
	if (sendBufCount == BUFFER_SIZE)
	{
		return;
	}

	sendMsgBuf[sendBufEnd].sender = SENDER_ID;
	sendMsgBuf[sendBufEnd].isBase = IS_BASE & 0x01;
	sendMsgBuf[sendBufEnd].origSend = 1;
	sendMsgBuf[sendBufEnd].hopCount = hop;
	sendMsgBuf[sendBufEnd].msg = msg;
	sendMsgBuf[sendBufEnd].data = data;
	
	if (++sendBufEnd == BUFFER_SIZE)
	{
		sendBufEnd = 0;
	}
	sendBufCount++;
}

void manageTransmit()
{
	if (sendBufCount == 0)
	{
		return;
	}
	
	// populate all the nibbles from the sendMsgBuf
	u08 nibbles[NUM_NIBBLES];
	nibbles[0] = (sendMsgBuf[sendBufStart].sender >> 3) & 0x0f;
	nibbles[1] = ((sendMsgBuf[sendBufStart].sender << 1) | sendMsgBuf[sendBufStart].isBase) & 0x0f;
	nibbles[2] = (sendSequence >> 4) & 0x0f;
	nibbles[3] = sendSequence & 0x0f;
	nibbles[4] = 0; // checksum
	nibbles[5] = ((sendMsgBuf[sendBufStart].hopCount << 1) | sendMsgBuf[sendBufStart].origSend) & 0x0f;
	nibbles[6] = (sendMsgBuf[sendBufStart].msg >> 4) & 0x0f;
	nibbles[7] = sendMsgBuf[sendBufStart].msg & 0x0f;
	nibbles[8] = (sendMsgBuf[sendBufStart].data >> 4) & 0x0f;
	nibbles[9] = sendMsgBuf[sendBufStart].data & 0x0f;
	
	// calculate the checksum
	nibbles[4] = checksum4(nibbles, NUM_NIBBLES);
	
	// set the pre-SB and SB
	sendWidths[0] = LOW_WIDTH;
	
	u08 i;
	for (i = 0; i < NUM_NIBBLES; i++)
	{
		sendWidths[1+i] = ((u16)nibbles[i]) * RESOLUTION + LOW_WIDTH + RESOLUTION;
	}
	
	if (++sendBufStart == BUFFER_SIZE)
	{
		sendBufStart = 0;
	}
	sendBufCount--;
	sendSequence++;
	sendWidthIndex = 0;
	TRANSMIT_OFF();
	enableOCR(HIGH_WIDTH);
	
	_delay_ms(1);
}

volatile u08 msgReady = 0;
volatile u08 errorHistory[100];
volatile u08 errorIndex = 0;
volatile u16 errorCount = 0;
void manageReceive()
{
	if (msgReady)
	{
		sbi(PORTA, 2);
		u08 i;
		for (i = msgReady-1; i > 0; i--)
		{
			recvWidths[i] -= recvWidths[i-1];
		}
		// for (i = 0; i < msgReady; i++)
		// {
			// uartPrint_u16(recvWidths[i]);
			// uartPrintChar(' ');
		// }
		// uartPrintChar(' ');
		u08 nibbles[NUM_NIBBLES];
		for (i = 1; i < msgReady; i++)
		{
			if (recvWidths[i] < 410)
			{
				nibbles[i-1] = 0;
			}
			else
			{
				nibbles[i-1] = (recvWidths[i]-410)/20;
			}
			// uartPrint_u08(nibbles[i-1]);
			// uartPrintChar(' ');
		}
		// uartPrintChar(' ');
		// uartPrint_u08(checksum4(nibbles, msgReady-1));
		// uartPrintString("\r\n");
		
		if (checksum4(nibbles, msgReady-1))
		{
			errorHistory[errorIndex] = 1;
		}
		else
		{
			errorHistory[errorIndex] = 0;
		}
		
		if (++errorIndex == 100)
		{
			u08 num = 0;
			for (i = 0; i < 100; i++)
			{
				num += errorHistory[i];
			}
			uartPrintString("Error Rate ");
			uartPrint_u16(errorCount++);
			uartPrintString(": ");
			uartPrint_u08(num);
			uartPrintString("\r\n");
			errorIndex = 0;
		}
		
		msgReady = 0;
		cbi(PORTA, 2);
	}
}

// ISR for transmitting (and eventually receiving)
ISR(TIMER1_COMPA_vect)
{
	if (recvWidthIndex >= 0)
	{
		msgReady = recvWidthIndex;
		recvWidthIndex = -1;
		disableOCR();
	}
	else
	{
		if (TRANSMIT_STATE())
		{
			TRANSMIT_OFF();
			if (sendWidthIndex == NUM_NIBBLES+1)
			{
				disableOCR();
			}
			OCR1A = sendWidths[sendWidthIndex++];
		}
		else
		{
			TRANSMIT_ON();
			if (sendWidthIndex == 0)
			{
				OCR1A = HIGH_WIDTH*2;
			}
			else
			{
				OCR1A = HIGH_WIDTH;
			}
		}
	}
}

ISR(PCINT0_vect)
{
	if (!RECEIVE_STATE())
	{
		return;
	}
	
	if (recvWidthIndex >= 0)
	{
		if (recvWidthIndex < NUM_NIBBLES+1)
		{
			recvWidths[recvWidthIndex] = TCNT1;
			OCR1A = (recvWidths[recvWidthIndex] + TIMEOUT);
			sbi(TIFR1, 1); // prevent immediate interrupt
			TIMSK1 = 0x02; // turn on OCR1A interrupt
			recvWidthIndex++;
		}
	}
	else
	{
		recvWidthIndex++;
		TCNT1 = 0;
		OCR1A = (TCNT1 + TIMEOUT);
		sbi(TIFR1, 1); // prevent immediate interrupt
		TIMSK1 = 0x02; // turn on OCR1A interrupt
	}
}
