#include "globals.h"
#include "swarmGlobals.h"
#include "ir.h"

/* buf = pointer to u08 array 
 * sender = robot id 
 * hopCount = integer number 0 - 3 indicating how many times the message
 * will be resent
 * origSend = 1 if original sender should be preserved
 * message = one of the defined messages
 */
void createMessage(u08 buf[MAX_MESSAGESIZE], u08 sender, u08 hopCount, u08 origSend, u08 message) {
	int i = 0;
	int ndx = 0;
	int even = 0;
	
	for (i = 0; i < 8; i++) {
		if (sender%2 == 0) {
			buf[ndx++] = 1;
			buf[ndx++] = 0;
		}
		else {
			buf[ndx++] = 1;
			buf[ndx++] = 1;
			buf[ndx++] = 0;
			even++;
		}
		sender = sender >> 1;
	}
	
	for (i = 0; i < 8; i++) {
		if (message%2 == 0) {
			buf[ndx++] = 1;
			buf[ndx++] = 0;
		}
		else {
			buf[ndx++] = 1;
			buf[ndx++] = 1;
			buf[ndx++] = 0;
			even++;
		}
		message = message >> 1;
	}
	
	for (i = 0; i < 2; i++) {
		if (hopCount%2 == 0) {
			buf[ndx++] = 1;
			buf[ndx++] = 0;
		}
		else {
			buf[ndx++] = 1;
			buf[ndx++] = 1;
			buf[ndx++] = 0;
			even++;
		}
		hopCount = hopCount >> 1;
	}
	
	if (origSend%2 == 0) {
		buf[ndx++] = 1;
		buf[ndx++] = 0;
	}
	else {
		buf[ndx++] = 1;
		buf[ndx++] = 1;
		buf[ndx++] = 0;
		even++;
	}

	if (BASE%2 == 0) {
		buf[ndx++] = 1;
		buf[ndx++] = 0;
	}
	else {
		buf[ndx++] = 1;
		buf[ndx++] = 1;
		buf[ndx++] = 0;
		even++;
	}
	
	if (even%2 == 0) {
		buf[ndx++] = 1;
		buf[ndx++] = 0;
	}
	else {
		buf[ndx++] = 1;
		buf[ndx++] = 1;
		buf[ndx++] = 0;
	}
	
	buf[ndx++] = 2;
}

void sendMessage(u08 buf[MAX_MESSAGESIZE]) {
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

