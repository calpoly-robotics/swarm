#define F_CPU 10000000L

#include <avr/io.h>
#include <util/delay.h>

#define sbi(a, b) ((a) |= 1 << (b))		// set bit
#define cbi(a, b) ((a) &= ~(1 << (b)))	// clear bit
#define tbi(a, b) ((a) ^= 1 << (b))		// toggles bit
#define gbi(a, b) ((a) & (1 << (b)))	// get bit

#define PIN PINA4

int main() {
	sbi(DDRA,PIN);
	for(;;) {
		sbi(PORTA, PIN);
		_delay_us(20);
		cbi(PORTA, PIN);
		_delay_us(30);
	}
}
