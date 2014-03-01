#ifndef SERIAL_H_
#define SERIAL_H_

#include "../globals.h"
#include <stdarg.h>

#define BAUD_RATE 19200

// must be <= 255
#define	UART_BUFFER_SIZE 255

#define DEBUG
// #define FLUSH_ON_NEWLINE 1
#define BLOCK_ON_UART_BUFFER_FULL 1

void uartInit();

void uartPrintChar(u08 data);
void uartPrintString(u08* str);
void uartPrintf(const u08* fmt, ...);
void uartPrint_u08(u08);
void uartPrint_u16(u16);

void uartPrintDebug(u08 len);

void uartFlush();

u08 uartDataReady();

u08 uartRead();

#endif /*SERIAL_H_*/ 