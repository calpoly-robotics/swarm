#include "globals.h"

// Notes in ms
// 1 = 1000
// 1/2 = 500
// 1/4 = 250
// 1/8 = 125


void init()
{
	sbi(DDRB, 4); // Buzzer out as output
}

void delay()
{
	TCCR0B = 0x00;
	_delay_ms(100);
}

int main()
{
	init();
	
	//uartInit();
	
  // set bit WGM01
  sbi(TCCR0A, WGM01);
  //cbi(TCCR0A, WGM00);
  // set bit COM0A0
  sbi(TCCR0A, COM0B0);
  cbi(TCCR0A, COM0B1);
  
  // set clock select bit
  //sbi(TCCR0B, CS02);
  TCCR0B = 0x04;
  OCR0A = 74;

  sei();

    //uartPrint_u08(TCCR0A);
    //uartPrintString("\n");
    //uartPrint_u08(TCCR0B);

   TCCR0B = 0x03;

   while (1)
	{
		
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

