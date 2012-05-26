#include "globals.h"
#include "ir.h"
#include <util/parity.h>
#include <stdlib.h>

volatile u08 irTransmitBuffer[8][MAX_MESSAGESIZE];
volatile u08 irTransmitStart = 0;
volatile u08 irTransmitEnd = 0;
volatile u08 irCurrentMsg[MAX_MESSAGESIZE];

inline void expandBit(u08 buf[], u08 *index, u08 bit)
{
	if (bit)
	{
		buf[(*index)++] = 1;
	}
	buf[(*index)++] = 1;
	buf[(*index)++] = 0;
}

void sendMessage(Message msg)
{
	u08 *buf = (u08 *) irTransmitBuffer[irTransmitEnd++];
	if (irTransmitEnd == 8)
	{
		irTransmitEnd = 0;
	}
	u08 i, index = 0;
	u08 parity = parity_even_bit((msg.hopCount << 4) | (msg.origSend << 2) | (msg.isBase << 1));
	parity += parity_even_bit(msg.sender);
	parity += parity_even_bit(msg.message);
	
	for (i = 0; i < 8; i++) {
		expandBit(buf, &index, msg.sender & 0x01);
		msg.sender >>= 1;
	}
	
	for (i = 0; i < 8; i++) {
		expandBit(buf, &index, msg.message & 0x01);
		msg.message >>= 1;
	}
	
	for (i = 0; i < 2; i++) {
		expandBit(buf, &index, msg.hopCount & 0x01);
		msg.hopCount >>= 1;
	}
	
	expandBit(buf, &index, msg.origSend & 0x01);
	expandBit(buf, &index, msg.isBase);
	expandBit(buf, &index, parity & 0x01);
	
	buf[index] = msg.type;
}

void loadNextMsg()
{
	u08 i;
	if (irTransmitEnd != irTransmitStart)
	{
		for (i = 0; i < MAX_MESSAGESIZE; i++)
		{
			irCurrentMsg[i] = irTransmitBuffer[irTransmitStart][i];
		}
		if (++irTransmitStart == 8)
		{
			irTransmitStart = 0;
		}
	}
}

void doSend()
{
	loadNextMsg();
	u08 i = 0;
	
	while (irCurrentMsg[i] < 2) {
		if (irCurrentMsg[i] == 0) 
			cbi(PORTB, IR_LED);
		else if (irCurrentMsg[i] == 1)
			sbi(PORTB, IR_LED);
		_delay_us(40);
		i++;
	}
}

