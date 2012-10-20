#include "globals.h"

void init()
{
	cbi(PORTD, 5); // AIN1
	sbi(DDRD, 5); // Data Direction Register <Letter (D)>, <#>
	cbi(PORTC, 0); // AIN2
	sbi(DDRC, 0); 
	cbi(PORTD, 7); // APWM
	sbi(DDRD, 7); 
	
	cbi(PORTD, 3); // BIN1
	sbi(DDRD, 3); 
	cbi(PORTD, 2); // BIN2
	sbi(DDRD, 2); 
	cbi(PORTD, 6); // BPWM
	sbi(DDRD, 6); 
	
	cbi(PORTD, 4); // STBY
	sbi(DDRD, 4); 
}

int main()
{
	init();
	
	//uartInit();
	
	// set bit WGM20 & WGM21
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	cbi(TCCR2A, WGM22);

	// set bit COM0A1
	cbi(TCCR2A, COM2A0);
	sbi(TCCR2A, COM2A1);
	// set bit COM0B1
	cbi(TCCR2A, COM2B0);
	sbi(TCCR2A, COM2B1);

	// set clock select bit CS20 & CS21
	TCCR0B = 0x03;

	sei();

	while (1)
	{
		_delay_ms(250);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 125; //D#5
	   _delay_ms(125);
		delay();
	   TCCR0B = 0x03; 
	   OCR0A = 167; //A#4
	   _delay_ms(375);
		delay();
	
		TCCR0B = 0x03;
	   OCR0A = 148; //C5
		_delay_ms(250);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 125; //D#5
	   _delay_ms(125);
		delay();
	   TCCR0B = 0x03; 
	   OCR0A = 167; //A#4
	   _delay_ms(375);
		delay();
	
		TCCR0B = 0x03;
	   OCR0A = 148; //C5
		_delay_ms(250);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 125; //D#5
	   _delay_ms(125);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 83; //A#5
	   _delay_ms(250);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 93; //G#5
	   _delay_ms(125);
		delay();
	
	   TCCR0B = 0x03;
	   OCR0A = 125; //D#5
	   _delay_ms(375);
		delay();
	   TCCR0B = 0x03;
	   OCR0A = 125; //D#5
	   _delay_ms(125);
		delay();

	   TCCR0B = 0x00;
	   _delay_ms(5000);      
   }

   return 0;
}

/*ISR(TIMER0_COMPA_vect)
{
	//sbi(PORTB, 4); // set Buzzer to 1
	
	//cbi(PORTB, 4); // set Buzzer to 0
	
	tbi(PORTB, 4); // toggle Buzzer value
	
	//gbi(PORTB, 4); // get Buzzer value
}*/

