/* TCCR0A */
// 10.0 MHZ crystal

// Need 2 timers
  // One for frequency
  // One for time


//fOCnA = fclk_I/O / (2 * N * (1 + OCRnA) )
//fOCnA = desired frequency of interrupt
//fclk_I/O = 10,000,000
// N = prescaler 
//OCRnA = result

int main()
{
  // set bit WGM01
  sbi(TCCR0A, WGM01);
  // set bit COM0A0
  sbi(TCCR0A, COM0A0);
  // set clock select bit
  sbi(TCCR0B, CS02);
  
  OCR0A = 74;

   while (1) ;

   return 0;
}

ISR(TIMER0_COMPA_vect)
{
   // do something here
	
	//sbi(PORTB, 4); // set Buzzer to 1
	
	//cbi(PORTB, 4); // set Buzzer to 0
	
	tbi(PORTB, 4); // toggle Buzzer value
	
	//gbi(PORTB, 4); // get Buzzer value
}



// Hightest frequency on piano: 4186 Hz
// Lowest frequency on piano: 32.7 Hz


// Disable timer or turn it low for turning it off?