#include "serial.h"
#include <stdio.h>

// NOTE: we don't actually ever need to reset or decrease the
// counter vars because in an unsigned 8-bit C var 255+1=0
// buffer clobbering could take place, but unlikely since we
// have a reasonable baudrate and newlines cause a flush(can be disalbed)
volatile u08 transmitBuffer[UART_BUFFER_SIZE];
volatile u08 transmitStart = 0;
volatile u08 transmitEnd = 0;
volatile u08 transmitCount = 0;

ISR(USART0_UDRE_vect) {
	if (transmitCount == 0) {
		cbi(UCSR0B, UDRIE0);
		return;
	}
	if (++transmitStart == UART_BUFFER_SIZE)
		transmitStart == 0;
	transmitCount--;
	UDR0 = transmitBuffer[transmitStart++];
		
}

#ifdef DEBUG
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

void uartPrintChar(u08 data) {
#ifdef BLOCK_ON_UART_BUFFER_FULL
	// block until there is room in the buffer
	while (transmitCount == UART_BUFFER_SIZE);
#endif

	transmitBuffer[transmitEnd] = data;
	if(++transmitEnd == UART_BUFFER_SIZE)
		transmitEnd = 0;
	transmitCount++;

	sbi(UCSR0B, UDRIE0);

	#ifdef FLUSH_ON_NEWLINE
	if(data=='\n')
		uartFlush();
	#endif
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

#else // don't do anything for these functions
inline void uartInit() {}

inline void uartPrintChar(u08 data) {}
inline void uartPrintString(u08* str) {}
inline void uartPrintf(const u08* fmt, ...) {}

inline void uartPrintDebug(u08 len) {}

inline void uartFlush() {}

inline u08 uartDataReady() {return 1;}

inline u08 uartRead() {return UDR0;}
#endif