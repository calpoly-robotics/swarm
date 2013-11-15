#include "serial.h"


void uartInit() {
	cli();

	// set theprescaler to match the baud rate
	u16 ubrr = (F_CPU/16/BAUD_RATE) - 1;
	UBRR0H = (u08)(ubrr >> 8);
	UBRR0H = (u08)(ubrr);

	// ensure double tx is off
	cbi(UCSR0A, U2X0);

	// enable rx, tx, and tx buffer interrupt;
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, UDRIE0);

	// set 8 bit data length
	sbi(UCSR0C, UCSZ01);
	sbi(UCSR0C, UCSZ00);
	
	// zero rest of register
	UCSR0C &= 0x06;

	sei();
}