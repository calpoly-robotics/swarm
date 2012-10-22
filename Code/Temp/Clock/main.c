#include "globals.h"

void init()
{
/*	cbi(PORTD, 5); // AIN1
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
	sbi(DDRD, 4); */
}

u32 getTime32()
{
	u16 lower;
	u16 upper;
	u32 time;
	
	u16 *upoint;
	u16 *lpoint;
	
	upoint = (u16*)&time;
	lpoint = (u16*)&time + 1;
	
	*upoint = upper;
	*lpoint = lower;
}

u16 upper16;
u32 time;

int main()
{
	//init();
	
	//uartInit();
	u16 timeUpper = 0;
	
	u16 *upoint;
	u16 *lpoint;
	
	upoint = (u16*)&time;
	lpoint = (u16*)&time + 1;
	
	*upoint = upper;
	*lpoint = lower;
	
	
	// clear bits
	cbi(TCCR3A, WGM30);
	cbi(TCCR3A, WGM31);
	cbi(TCCR3B, WGM32);
	cbi(TCCR3B, WGM33);
	
	// set bit COM0A1
	cbi(TCCR3A, COM3A0);
	cbi(TCCR3A, COM3A1);
	// set bit COM0B1
	cbi(TCCR3A, COM3B0);
	cbi(TCCR3A, COM3B1);

	// set clock select bit CS30 & CS32
	sbi(TCCR3B, CS30);
	sbi(TCCR3B, CS32);
	//TCCR3B = 0x05;

	sei();

	while (1)
	{
		*upoint = upper16;
		*lpoint = TCNT3H;
		
		_delay_ms(1000);
   }

   return 0;
}

ISR(TIMER3_OVF_vect)
{
	upper16++;
}
