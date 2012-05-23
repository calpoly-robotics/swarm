#include "globals.h"
#include "ir.h"
#include <util/parity.h>


/* buf = pointer to u08 array 
 * sender = robot id 
 * hopCount = integer number 0 - 3 indicating how many times the message
 * will be resent
 * origSend = 1 if original sender should be preserved
 * message = one of the defined messages
 */
void createMessage(u08 buf[], u08 sender, u08 hopCount, u08 origSend, u08 message) {
	u08 i, index = 0, even = 0;
	
	u08 metaData = 0;
	metaData |= (hopCount << 4) | (origSend << 2) | (BASE << 1);
	u08 parityBit = (parity_even_bit(sender) + parity_even_bit(message) + parity_even_bit(metaData));
	
	for (i = 0; i < 8; i++) {
		if (sender & 0x01) {
			buf[index++] = 1;
			buf[index++] = 1;
			buf[index++] = 0;
			even++;
		}
		else {
			buf[index++] = 1;
			buf[index++] = 0;
		}
		sender = sender >> 1;
	}
	
	for (i = 0; i < 8; i++) {
		if (message & 0x01) {
			buf[index++] = 1;
			buf[index++] = 1;
			buf[index++] = 0;
			even++;
		}
		else {
			buf[index++] = 1;
			buf[index++] = 0;
		}
		message = message >> 1;
	}
	
	for (i = 0; i < 2; i++) {
		if (hopCount & 0x01) {
			buf[index++] = 1;
			buf[index++] = 1;
			buf[index++] = 0;
			even++;
		}
		else {
			buf[index++] = 1;
			buf[index++] = 0;
		}
		hopCount = hopCount >> 1;
	}
	
	if (origSend & 0x01) {
		buf[index++] = 1;
		buf[index++] = 1;
		buf[index++] = 0;
		even++;
	}
	else {
		buf[index++] = 1;
		buf[index++] = 0;
	}

	if (BASE & 0x01) {
		buf[index++] = 1;
		buf[index++] = 1;
		buf[index++] = 0;
		even++;
	}
	else {
		buf[index++] = 1;
		buf[index++] = 0;
	}
	
	if (parityBit & 0x01) {
		buf[index++] = 1;
		buf[index++] = 1;
		buf[index++] = 0;
	}
	else {
		buf[index++] = 1;
		buf[index++] = 0;
	}
	
	buf[index++] = 2;
}

void sendMessage(u08 buf[]) {
	int i = 0;
	
	while (buf[i] < 2) {
		if (buf[i] == 0) 
			cbi(PORTB, IR_LED);
		else if (buf[i] == 1)
			sbi(PORTB, IR_LED);
		_delay_ms(PULSE_WIDTH);
		i++;
		//tbi(PORTB, RED_LED);
	}
}

