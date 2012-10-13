#include "ir.h"
#include <util/parity.h>
#include <stdlib.h>

#define IR_BUFFER_SIZE 8
#define IR_START_LEN 3
#define IR_OCR_VAL 39
#define IR_OCR_HALF_VAL 19

volatile u08 irTransmitBuffer[IR_BUFFER_SIZE][MAX_MESSAGESIZE];
volatile u08 irTransmitStart = 0;
volatile u08 irTransmitEnd = 0;
volatile u08 irCurrentMsg[MAX_MESSAGESIZE];
volatile u08 irTransmitIndex;

// initializes the IR transmitting (and eventually receiving)
void initIR()
{
	TCCR1A = 0x00; // CTC mode
	TCCR1B = 0x0A; // CTC mode and clk/8 prescalar
	TCCR1C = 0x00;
	OCR1A = IR_OCR_VAL; // interrupt every 125 counts
	TIMSK1 = 0x00; // turn off OCR1A interrupt
	sei();
}

// expands a bit into pulses and puts it into the passed buffer at the passed index
static void expandBit(u08 buf[], u08 *index, u08 bit)
{
	if (bit)
	{
		buf[(*index)++] = 1;
	}
	buf[(*index)++] = 1;
	buf[(*index)++] = 0;
}

/* 
 * Takes a Message, decodes the data from the struct, and expands all the bits
 * of data into pulses. Places the pulse data into the circular transmit buffer/
 *
 * msg - The message which you wish to send.
 */
void sendMessage(Message msg)
{
	u08 i, parity, index = 0;
	
	// get a local reference to the next free buffer slot
	u08 *buf = (u08*)irTransmitBuffer[irTransmitEnd++];
	if (irTransmitEnd == IR_BUFFER_SIZE)
	{
		irTransmitEnd = 0;
	}
	
	// calculate the parity before messing with the data
	parity = parity_even_bit((msg.hopCount << 4) | (msg.origSend << 2) | (msg.isBase << 1));
	parity += parity_even_bit(msg.sender);
	parity += parity_even_bit(msg.message);
	
	// insert the start pulse
	for (i = 0; i < IR_START_LEN; i++)
	{
		buf[index++] = 1;
	}
	buf[index++] = 0;
	
	// expand and insert the sender byte
	for (i = 0; i < 8; i++)
	{
		expandBit(buf, &index, msg.sender & 0x01);
		msg.sender >>= 1;
	}
	
	// expand and insert the message byte
	for (i = 0; i < 8; i++)
	{
		expandBit(buf, &index, msg.message & 0x01);
		msg.message >>= 1;
	}
	
	// expand and insert the hopCout bits
	for (i = 0; i < 2; i++)
	{
		expandBit(buf, &index, msg.hopCount & 0x01);
		msg.hopCount >>= 1;
	}
	
	// expand and insert the origSend, isBase, and parity bits
	expandBit(buf, &index, msg.origSend & 0x01);
	expandBit(buf, &index, msg.isBase);
	expandBit(buf, &index, parity & 0x01);
	
	// use the type as the end marker
	buf[index] = msg.type;
}

/*
 * If there's something in the transmit buffer and we aren't currently transmitting,
 * copies it into the irCurrentMsg buffer and enables transmitting.
 */
void manageTransmit()
{
	// return if there's nothing to send or we are currently transmitting
	if (irTransmitEnd == irTransmitStart || TIMSK1 & 0x02)
		return;
	
	// load the next message into the irCurrentMsg array
	u08 i;
	for (i = 0; i < MAX_MESSAGESIZE; i++)
	{
		irCurrentMsg[i] = irTransmitBuffer[irTransmitStart][i];
	}
	if (++irTransmitStart == IR_BUFFER_SIZE)
	{
		irTransmitStart = 0;
	}
	
	// enable transmitting
	irTransmitIndex = 0;
	TCNT1 = -IR_OCR_HALF_VAL; // set counter to -62 so first interrupt is 1.5 duration
	TIMSK1 = 0x02; // turn on OCR1A interrupt
}


// ISR for transmitting (and eventually receiving)
ISR(TIMER1_COMPA_vect)
{
	if (irCurrentMsg[irTransmitIndex] > 1)
	{
		TIMSK1 = 0x00; // turn off OCR1A interrupt
		return;
	}
	
	if (irCurrentMsg[irTransmitIndex] == 0)
		cbi(PORTB, IR_LED);
	else if (irCurrentMsg[irTransmitIndex] == 1)
		sbi(PORTB, IR_LED);
	
	irTransmitIndex++;
}
