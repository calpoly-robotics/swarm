#include "../globals.h"

#define TIME_UNIT 128
#define HALF_TIME_UNIT TIME_UNIT/2


typedef struct {
	u08 response;
	u08 checksum;
	u08 length;
	u08 data[128];
} oneWireMsg;


inline u08 oneWireCheckForBase()
{
	// output low pulse
	sbi(DDRD, 1); // set PD1 as output
	cbi(PORTD, 1); // set output low
	_delay_us(TIME_UNIT);
	
	// allow base to respond
	sbi(PORTD, 1); // set output high
	cbi(DDRD, 1); // set PD1 as input
	sbi(PORTD, 1); // turn on pull-up
	
	u08 startBit = !gbi(PIND, 1);
	_delay_us(TIME_UNIT);
	return startBit;
}

inline oneWireMsg readOneWire()
{
	u08 i, j;
	oneWireMsg msg;

	// get response bit
	msg.response = gbi(PIND, 1);
	_delay_us(TIME_UNIT);
	
	// get checksum
	msg.checksum = 0;
	for (i = 0; i < 4; i++)
	{
		msg.checksum = (msg.checksum << 1) | (gbi(PIND, 1) && 0x01);
		_delay_us(TIME_UNIT);
	}
	
	// get length field
	msg.length = 0;
	for (i = 0; i < 7; i++)
	{
		msg.length = (msg.length << 1) | (gbi(PIND, 1) && 0x01);
		_delay_us(TIME_UNIT);
	}
	
	// get data
	for (i = 0; i < msg.length; i++)
	{
		msg.data[i] = 0;
		for (j = 0; j < 8; j++)
		{
			msg.data[i] = (msg.data[i] << 1) | (gbi(PIND, 1) && 0x01);
			_delay_us(TIME_UNIT);
		}
	}
	
	return msg;
}