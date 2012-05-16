/*
 *  serial.c
 *
 *
 *  Created by Christopher MacKenzie and Brian Gomberg on 2/19/12.
 *  Copyright 2012 Cal Poly SLO Robotics Club. All rights reserved.
 *
 */
 
 /*! @file
	Implements support functions for serial communication over uart0/uart1.
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

volatile u08 transmitBuffer0[256];
volatile u08 transmitStart0 = 0;
volatile u08 transmitEnd0 = 0;

ISR(USART_UDRE_vect)
{
	tbi(PORTB, 0);
	if (transmitStart0 != transmitEnd0)
	{
		UDR0 = transmitBuffer0[transmitStart0++];
	}
	else
	{
		UCSR0B &= ~(1 << UDRIE0);
	}
}

/**
 * Transmits the given data over UART0 by adding the data to the transmit buffer.
 *
 * @param data The data to transmit over UART0.
 */
void uart0Transmit_u08(u08 data)
{
	transmitBuffer0[transmitEnd0++] = data;
	UCSR0B |= (1 << UDRIE0);
}

/**
 * Transmits the given u16 over UART0 by pushing the high byte of the u16
 * followed by the low byte into the transmit buffer.
 *
 * @param numData The number of bytes to send.
 * @param data The data to transmit over UART0.
 */
void uart0Transmit_u16(u16 data)
{
	uart0Transmit_u08(data >> 8); // upper byte
	uart0Transmit_u08(data); // lower byte
}

/**
 * Transmits the given data over UART0 by adding the data to the transmit buffer.
 *
 * @param numData The number of bytes to send.
 * @param data The data to transmit over UART0.
 */
void uart0TransmitMultiple(u08 numData, u08 *data)
{
	u08 i;
	for(i = 0; i < numData; i++)
	{
		uart0Transmit_u08(data[i]);
	}
}

/**
 * Receives the data from UART0 and returns the value. Will not work when the RX ISR is in use.
 *
 * @return The data from the UART0 transmission.
 */
u08 uart0Receive_u08()
{
	//Wait for the data to be received.
	while(!(UCSR0A & (1 << RXC0)));

	return UDR0;
}

void uart0PrintString(u08 *str)
{
	while(*str)
	{
		uart0Transmit_u08(*str);
		str++;
	}
}

/**
 * Flush the receive buffer FIFO, code from Atmega documentation.
 */
void uart0Flush()
{
	u08 temp;

	//Read from the register until the buffer is cleared and assign it to a dummy variable.
	while(UCSR0A & (1 << RXC0))
		temp = UDR0;
}
