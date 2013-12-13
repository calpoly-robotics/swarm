#ifndef SERIAL_H_
#define SERIAL_H_

#include "../globals.h"
#include <stdarg.h>

#define BAUD_RATE 19200

#define FLUSH_ON_NEWLINE 1

void uartInit();

void uartPrintChar(u08 data);
void uartPrintChar2(u16 data);
void uartPrintString(u08* str);
void uartPrintf(const u08* fmt, ...);

void uartPrintNibble(u08 nibble);
void uartPrint_u08(u08 num);
void uartPrint_u16(u16 num);
void uartPrint_u32(u32 num);
void uartPrint_u08_dec(u08 num);
void uartPrint_u16_dec(u16 num);
void uartPrint_u32_dec(u32 num);

void uartPrintDebug(u08 len);

void uartFlush();

u08 uartDataReady();

u08 uartRead();

#endif /*SERIAL_H_*/ 