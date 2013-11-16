#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

// CPU speed 10MHz
#define F_CPU 10000000L


// Define shorthand datatypes
typedef uint8_t 	u08;
typedef uint16_t 	u16;
typedef uint32_t 	u32;
typedef int8_t	 	s08;
typedef int16_t 	s16;
typedef int32_t 	s32;

// Bit manipulations macros
#define sbi(a, b) ((a) |= 1 << (b))		// set bit
#define cbi(a, b) ((a) &= ~(1 << (b)))	// clear bit
#define tbi(a, b) ((a) ^= 1 << (b))		// toggles bit
#define gbi(a, b) ((a) & (1 << (b)))	// get bit


#endif /* GLOBALS_H_ */