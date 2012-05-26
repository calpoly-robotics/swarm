/*! @file
	Implements support functions for serial communication over UART.
	Code from the Cal Poly SLO Robotics Club Xiphos Board libraries.
	Originally created by Brian Gomberg and Chris MacKenzie. 
*/

#include "globals.h"
#define BAUD_RATE 9600

/**
 * Initialize the enabled UARTs.
 * Normally only called by the initialize() function in utility.c.
 */
inline void uartInit()
{
	//Convert the baud rate to the desired value to put in the register using a prescalar.
	u16 ubrr = (F_CPU/16/BAUD_RATE) - 1;

	//Set the high and low register with the value calculated from the baud rate.
	UBRR0H = (u08)(ubrr >> 8);
	UBRR0L = (u08)(ubrr);

	//Make sure that the double transmission speed bit is low turning it off.
	UCSR0A &= ~(1 << U2X0);

	//Enable receive, transmit, and the transmit buffer empty interrupt.
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << UDRIE0);
	//Set the size bits in the status register to make it 8 bit data length.
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	//Make sure everything else in the register is 0.
	UCSR0C &= 0x06;

	sei();
}

volatile u08 transmitBuffer[256];
volatile u08 transmitStart = 0;
volatile u08 transmitEnd = 0;

ISR(USART_UDRE_vect)
{
	tbi(PORTB, 0);
	if (transmitStart != transmitEnd)
	{
		UDR0 = transmitBuffer[transmitStart++];
	}
	else
	{
		UCSR0B &= ~(1 << UDRIE0);
	}
}

/**
 * Transmits the given data over UART by adding the data to the transmit buffer.
 *
 * @param data The data to transmit over UART.
 */
void uartPrintChar(u08 data)
{
	transmitBuffer[transmitEnd++] = data;
	UCSR0B |= (1 << UDRIE0);
}

/**
 * Transmits the given u16 over UART by pushing the high byte of the u16
 * followed by the low byte into the transmit buffer.
 *
 * @param numData The number of bytes to send.
 * @param data The data to transmit over UART.
 */
void uartPrintChar2(u16 data)
{
	uartPrintChar(data >> 8); // upper byte
	uartPrintChar(data); // lower byte
}

/**
 * Transmits the given string over UART by transmitting one char (u08) at a time.
 *
 * @param str The null-terminated string to be sent.
 */
void uartPrintString(u08 *str)
{
	while(*str)
	{
		uartPrintChar(*str++);
	}
}

void uartPrint_u08(u08 num)
{
	uartPrintChar('0' + num/100);
	uartPrintChar('0' + (num % 100)/10);
	uartPrintChar('0' + num % 10);
}

/**
 * Flush the receive buffer FIFO, code from Atmega documentation.
 */
void uartFlush()
{
	u08 temp;

	//Read from the register until the buffer is cleared and assign it to a dummy variable.
	while(UCSR0A & (1 << RXC0))
		temp = UDR0;
}

/**
 * Receives the data from UART and returns the value.
 *
 * @return Whether or not there is valid data in the UART receive buffer.
 */
inline u08 uartDataAvailable()
{
	return UCSR0A & (1 << RXC0);
}

/**
 * Receives the data from UART and returns the value.
 *
 * @return The data from the UART transmission.
 */
u08 uartRead()
{
	//Wait for the data to be received.
	while(!uartReady());

	return UDR0;
}
