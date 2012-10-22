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

volatile u16 upper16;
volatile u32 time;

int main()
{
	//init();
	
	uartInit();
	//u16 timeUpper = 0;
	upper16 = 0;
	
	u16 lowTmp;
	u16 upper = 123;
	u16 lower = 4660;
	
	u16 *upoint;
	u16 *lpoint;
	
	lpoint = (u16*)&time;
	upoint = (u16*)&time + 1;
	
	//*upoint = upper;
	//*lpoint = lower;
	
	// clear bits
	cbi(TCCR3A, WGM30);
	cbi(TCCR3A, WGM31);
	cbi(TCCR3B, WGM32);
	cbi(TCCR3B, WGM33);
	
	// clear bit COM3A
	cbi(TCCR3A, COM3A0);
	cbi(TCCR3A, COM3A1);
	// clear bit COM3B
	cbi(TCCR3A, COM3B0);
	cbi(TCCR3A, COM3B1);
	
	// set Overflow interrupt enable bit
	sbi(TIMSK3, TOIE3);

	// set clock select bit CS30 & CS32
	sbi(TCCR3B, CS30);
	cbi(TCCR3B, CS31);
	sbi(TCCR3B, CS32);
	//TCCR3B = 0x05;

	sei();

	_delay_ms(5000);
	uartPrintString("\r\nHello?\r\n");
	
	while (1)
	{
		*upoint = upper16;
		lowTmp = TCNT3;
		*lpoint = lowTmp;
		
		uartPrint_u16(upper16);
		uartPrintString(",");
		uartPrint_u16(lowTmp);
		uartPrintString(",");
		uartPrint_u32(time);
		uartPrintString(" ");
		_delay_ms(1000);
   }

   return 0;
}

ISR(TIMER3_OVF_vect)
{
	upper16++;
}
