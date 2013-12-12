#define F_CPU 10000000L

#include <avr/io.h>
#include <util/delay.h>

#define PIN 0

int main() {
	DDRB |= (1 << PIN);
	PORTB |= (1 << PIN);
	for(;;) {
		_delay_ms(2000);
		PINB |= (1 << PIN);
	}
}
