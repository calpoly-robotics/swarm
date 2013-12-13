#include "serial.h"
#include <stdio.h>

#define BUFFER_SIZE 512

#define waitForRoom() while (transmitCount == BUFFER_SIZE)

volatile u08 transmitBuffer[BUFFER_SIZE];
volatile u08 transmitCount = 0;
volatile u08 transmitStart = 0;
volatile u08 transmitEnd = 0;

void uartInit() {
	cli();

	// set theprescaler to match the baud rate
	u16 ubrr = (F_CPU/16/BAUD_RATE) - 1;
	UBRR0 = ubrr;
	//UBRR0H = (u08)(ubrr >> 8);
	//UBRR0H = (u08)(ubrr);

	// enable rx, tx, and tx buffer interrupt;
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, UDRIE0);

	// set 8 bit data length
	sbi(UCSR0C, UCSZ01);
	sbi(UCSR0C, UCSZ00);

	sei();
}

ISR(USART0_UDRE_vect) {
	if (transmitCount == 0) {
		cbi(UCSR0B, UDRIE0);
		return;
	}
	
	UDR0 = transmitBuffer[transmitStart];
	if (++transmitStart == BUFFER_SIZE)
		transmitStart = 0;

	transmitCount--;
}

void uartPrintChar(u08 data) {
	waitForRoom();	

	transmitBuffer[transmitEnd++] = data;
	sbi(UCSR0B, UDRIE0);

	if (++transmitEnd == BUFFER_SIZE)
		transmitEnd = 0;
	transmitCount++;
}

void uartPrintChar2(u16 data) {
	uartPrintChar(data >> 8);
	uartPrintChar(data);
}

void uartPrintString(u08* str) {
	while (*str) {
		uartPrintChar(*str++);
	}
}

void uartPrintf(const u08* fmt, ... ) {
	u08 buffer[256];
	va_list args;
	va_start( args, fmt);
	vsprintf(buffer, fmt, args);
	uartPrintString(buffer);
	va_end(args);
}

void uartPrintNibble(u08 nibble) {
	if (nibble > 15)
		uartPrintChar('b'); // wrong
	else if (nibble > 9)
		uartPrintChar('A' + (nibble - 10));
	else
		uartPrintChar('0' + nibble);
}

void uartPrint_u08(u08 data) {
	uartPrintNibble(data >> 4);
	uartPrintNibble(data & 0xF);
}

void uartPrint_u16(u16 data) {
	uartPrint_u08(data >> 8);
	uartPrint_u08(data & 0xFF);
}

void uartPrint_u32(u32 data) {
	uartPrint_u16(data >> 16);
	uartPrint_u16(data & 0xFFFF);
}

void uartPrint_u08_dec(u08 num)
{
	if (num >= 100)
	{
		uartPrintChar('0' + num/100);
	}
	else
	{
		uartPrintChar(' ');
	}
	if (num >= 10)
	{
		uartPrintChar('0' + (num % 100)/10);
	}
	else
	{
		uartPrintChar(' ');
	}
	uartPrintChar('0' + num % 10);
}

void uartPrint_u16_dec(u16 num)
{
	uartPrintChar('0' + num/10000);
	uartPrintChar('0' + (num % 10000)/1000);
	uartPrintChar('0' + (num % 1000)/100);
	uartPrintChar('0' + (num % 100)/10);
	uartPrintChar('0' + num % 10);
}

void uartPrint_u32_dec(u32 num)
{
	uartPrintChar('0' + num/1000000000);
	uartPrintChar('0' + (num % 1000000000)/100000000);
	uartPrintChar('0' + (num % 100000000)/10000000);
	uartPrintChar('0' + (num % 10000000)/1000000);
	uartPrintChar('0' + (num % 1000000)/100000);
	uartPrintChar('0' + (num % 100000)/10000);
	uartPrintChar('0' + (num % 10000)/1000);
	uartPrintChar('0' + (num % 1000)/100);
	uartPrintChar('0' + (num % 100)/10);
	uartPrintChar('0' + num % 10);
}

void uartPrintDebug(u08 len) {
	uartPrintChar('8');
	for (;len>0;len--) {
		uartPrintChar('=');
	}
	uartPrintString("D\n");
}

/**
 * Flush the receive buffer
 */
// #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
void uartFlush() {
	u08 tmp;

	// read from the register until the buffer is cleared
	// and assign it to a dummy var
	while (gbi(UCSR0A, RXC0))
		tmp = UDR0;
}
// #pragma GCC diagnostic warning "-Wunused-but-set-variable"

inline u08 uartDataReady() {
	return gbi(UCSR0A, RXC0);
}

u08 uartRead() {
	// block until data is ready
	while (!uartDataReady());

	return UDR0;
}
