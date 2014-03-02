#include "ir.h"
#include "../Tasks/irTask.h"
#include "eeprom.h"
#include "serial.h"
#include <string.h>

#define ALL_RX_MASK (1 << RECIEVE_PIN4)

u08 senderId = 0;
u08 transmitting = 0;

volatile Message sendMsgBuf[BUFFER_SIZE];
volatile u08 sendBufCount = 0;
volatile u08 sendBufStart = 0;
volatile u08 sendBufEnd = 0;

volatile Message recvMsgBuf[BUFFER_SIZE];
volatile u08 recvBufCount = 0;
volatile u08 recvBufStart = 0;
volatile u08 recvBufEnd = 0;
volatile u08 sendSequence = 0;
volatile s08 sendWidthIndex = 0;
volatile u16 sendWidths[NUM_NIBBLES+1];

volatile s08 recvWidthIndex = -1;
volatile u16 recvWidths[NUM_NIBBLES+1];

volatile u08 msgReady = 0;

inline u08 getSenderId() {
	return senderId;
}

void enablePCINT()  {
	// uartPrintChar('e');
	// uartPrintChar('\n');
	sbi(PCICR, PCIE2);
	PCMSK2 = ALL_RX_MASK;
}

void disablePCINT() {
	// uartPrintChar('d');
	// uartPrintChar('\n');
	cbi(PCICR, PCIE2);
}

void initIR() {
	// doesn't have to be first if this causes problems...
	senderId = eeprom_read_byte((u08*)IR_SENDER_ID_ADDRESS);

	// 0 is init val
	//TCCR1A = 0; // CTC mode
	sbi(TCCR1B, WGM12);

	// set prescaler to 1
	sbi(TCCR1B, CS10);

	sei();
	sbi(DDRC, TRANSMIT_PIN);
	enablePCINT();
}

inline void enableOCR(u16 val) {
	TCNT1 = 0; // reset timer
	OCR1A = val;
	// pretty sure that line is useless
	sbi(TIFR1, OCF1A); // prevent immediate interrupt
	sbi(TIMSK1, OCIE1A); // turn on OCR1A intterupt
}

inline void disableOCR() {
	cbi(TIMSK1, OCIE1A);
}

static inline void sendBufHasSpace() {
	if (sendBufCount > BUFFER_SIZE - 4) // arbitrary number
		txBufferFull();
}

static void retransmit(Message msg) {
	msg.ttl--;
	sendBufHasSpace();

	if(sendBufCount == BUFFER_SIZE)
		return;

	sendMsgBuf[sendBufEnd] = msg;

	if (++sendBufEnd == BUFFER_SIZE)
		sendBufEnd = 0;
	sendBufCount++;
}

void sendMessage(u08 ttl, msg_type msg, u08 data) {
	sendBufHasSpace();

	if (sendBufCount == BUFFER_SIZE) // if buffer is full, ignore message
		return;

	sendMsgBuf[sendBufEnd].sender = senderId;
	sendMsgBuf[sendBufEnd].isBase = 0;
	sendMsgBuf[sendBufEnd].origSend = 1;
	sendMsgBuf[sendBufEnd].ttl = ttl;
	sendMsgBuf[sendBufEnd].msg = msg;
	sendMsgBuf[sendBufEnd].data = data;

	if (++sendBufEnd == BUFFER_SIZE)
		sendBufEnd = 0;
	sendBufCount++;
}

int readMessage(Message* msg) {
	if (recvBufCount == 0)
		return 1;
	// uartPrintChar('z');
	// uartPrintf("Count:%d\tEnd:%d\n",recvBufCount,recvBufEnd);

	*msg = recvMsgBuf[recvBufEnd];
	// memcpy(msg,(void*)recvMsgBuf + recvBufEnd*sizeof(Message),sizeof(Message));
	// Message tmp = recvMsgBuf[recvBufEnd];
	// uartPrintf("Type:%.3u\tData:%u\n",tmp.msg,tmp.data);

	recvBufCount--;
	if (++recvBufStart == BUFFER_SIZE)
		recvBufStart = 0;

	return 0;
}

u08 getRecvBufCount() {
	return recvBufCount;
}
// 
/**
 * Takes an array of bytes and calculates the 4bit checksum. Will work for
 * bytes where the lower nibble contains data (non-zero)
 */
u08 checksum4(u08* data, u08 len) {
	u08 i, result = 0;
	for (i = 0; i < len; i++) {
		result ^= (data[i] >> 4) ^ (data[i] & 0x0F);
	}

	return result;
}

void manageTransmit() {
	if (sendBufCount == 0)
		return;

	// populate all the nibbles
	u08 nibbles[NUM_NIBBLES];
	nibbles[0] = (sendMsgBuf[sendBufStart].sender >> 3) & 0x0F;
	nibbles[1] = ((sendMsgBuf[sendBufStart].sender << 1) | sendMsgBuf[sendBufStart].isBase) & 0x0F;
	nibbles[2] = (sendSequence >> 4) & 0x0F;
	nibbles[3] = sendSequence & 0x0F;
	nibbles[4] = 0; // checksum
	nibbles[5] = ((sendMsgBuf[sendBufStart].ttl << 1) | sendMsgBuf[sendBufStart].origSend) & 0x0F;
	nibbles[6] = (sendMsgBuf[sendBufStart].msg >> 4) & 0x0F;
	nibbles[7] = sendMsgBuf[sendBufStart].msg & 0x0F;
	nibbles[8] = (sendMsgBuf[sendBufStart].data >> 4) & 0x0F;
	nibbles[9] = sendMsgBuf[sendBufStart].data & 0x0F;

	// calculate the checksum
	nibbles[4] = checksum4(nibbles, NUM_NIBBLES);

	// set the pre-start bit and start bit
	sendWidths[NUM_NIBBLES] = HIGH_WIDTH; // so that we can get the final falling edge
	u08 i;
	for (i = 0; i < NUM_NIBBLES; i++) {
		// nibble in time + time to fall low + plus a little more for good measure
		sendWidths[i] = ((u16)nibbles[i]*RESOLUTION) + LOW_WIDTH + RESOLUTION;
		uartPrintf("%d\t%d\n", sendWidths[i],nibbles[i]);
	}
	uartPrintf("%d\n\n",sendWidths[10]);

	if (++sendBufStart == BUFFER_SIZE)
		sendBufStart = 0;

	sendBufCount--;
	// sendSequence++;
	sendWidthIndex = -1;
	TRANSMIT_OFF();
	enableOCR(HIGH_WIDTH);
	disablePCINT();
	transmitting = 1;
}

void manageRecieve() {
	if (msgReady == NUM_NIBBLES+1) {
		msgReady = 0;
		// sbi(PINA, 1);
		// uartPrintString("MR\n");

		u08 i;
		for (i = NUM_NIBBLES+1; i > 0; i--) {
			// technically, recvWidths[0] will be random data
			// but it's only reading from random memory, so we don't care
			recvWidths[i] -= recvWidths[i-1];
		}

		u08 nibbles[NUM_NIBBLES];
		for (i = 1; i < NUM_NIBBLES+1; i++) {
			// if (recvWidths[i] < HIGH_WIDTH + LOW_WIDTH + RESOLUTION/2)
			// 	nibbles[i-1] = 0;
			// else
				nibbles[i-1] = (recvWidths[i]- HIGH_WIDTH - LOW_WIDTH - RESOLUTION/2)/RESOLUTION;
		}

		for (i=0; i < NUM_NIBBLES; i++) {
			uartPrintf("%d\t%2d\n",recvWidths[i+1],nibbles[i]);
		}
		uartPrintChar('\n');

		u08 msgChecksum = nibbles[4] & 0x0F;
		nibbles[4] = 0; // this is how the nibbles were when the checksum happened

		u08 tmpChecksum = checksum4(nibbles, NUM_NIBBLES);
		if (tmpChecksum != msgChecksum) {
			// uartPrintf("Expected:%x\tGot:%x\n", msgChecksum, tmpChecksum);
			return;
		}

		u08 tmpSender = (nibbles[0] << 2 | nibbles[1] >> 1) & 0x7F;
		if (senderId == tmpSender)
			return; 	// we sent this. Ignore

		recvMsgBuf[recvBufEnd].sender = tmpSender;
		recvMsgBuf[recvBufEnd].ttl = (nibbles[5] >> 1) & 0x07;
		recvMsgBuf[recvBufEnd].isBase = (nibbles[5]) & 0x01;
		recvMsgBuf[recvBufEnd].msg = nibbles[6] << 4 | (nibbles[7] & 0x0F);
		recvMsgBuf[recvBufEnd].data = nibbles[8] << 4 | (nibbles[9] & 0x0F);

		if (++recvBufEnd == BUFFER_SIZE)
			recvBufEnd = 0;
		recvBufCount++;
	}
}

ISR(TIMER1_COMPA_vect) {
	if (recvWidthIndex > -1) { // timeout occured. Message done or error
		uartPrintf("%d\n",recvWidthIndex);
		if (recvWidthIndex == NUM_NIBBLES+1)
			msgReady = recvWidthIndex;
		recvWidthIndex = -1;
		PCMSK2 = ALL_RX_MASK;
		enablePCINT();
		disableOCR();
		// sbi(PINA, 1);
	} else {
		if (TRANSMIT_STATE()) { // the emitter is on
			TRANSMIT_OFF();

			if (++sendWidthIndex == NUM_NIBBLES + 1) {// last nibble
				sbi(PINA,1);
				disableOCR();
				enablePCINT();
				return;
			}
			OCR1A = LOW_WIDTH;
		} else {
			TRANSMIT_ON();
			if (sendWidthIndex == -1)
				OCR1A = HIGH_WIDTH*2; // start bit is long
			else if (sendWidthIndex < NUM_NIBBLES+1) {
				//sbi(PINA,1);
				OCR1A = sendWidths[sendWidthIndex];
			}
		}
	}
}

ISR(PCINT2_vect) {
	u16 tmpTime = TCNT1;
	//sbi(PINA,1);

	if (transmitting) // don't recieve if we're tx
		return;

	if (PINC & ALL_RX_MASK) // if pin is low, then this is a falling edge. Fuck falling edges
		return;

	// // uartPrintChar('0'+recvWidthIndex);
	if (recvWidthIndex > -1) { // not the first nibble
		recvWidths[recvWidthIndex] = tmpTime;
		recvWidthIndex++;

		OCR1A = tmpTime + TIMEOUT;

		// sbi(TIFR1, OCR1A);
		// sbi(TIMSK1, OCIE1A);
	} else {
		// cbi(PINA, 1);
		PCMSK2 = (~PINC) & ALL_RX_MASK;
		recvWidthIndex = 0;
		enableOCR(TIMEOUT);

		// sbi(TIFR1, OCR1A);
		// sbi(TIMSK1, OCIE1A);
	}
}