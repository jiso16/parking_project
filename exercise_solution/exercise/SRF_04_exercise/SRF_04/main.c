#include<avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include "clcd_D8.h"
//
#define Trigger_1       PORTD|=1  //초음파 트리거
#define Trigger_0       PORTD&=~1 //초음파 트리거
#define Echo            (PIND&2)  //초음파 에코
//
unsigned int range;
//
void getEcho(void)
{
	while(!Echo);            // high가 될때까지 대기 //
	TCNT1=0; TCCR1B=2;       // 카운터 시작, 8분주 = 0.5us //
	while(Echo);             // low가 될때까지 대기 //
	TCCR1B=8;                // 카운터 정지 //
	range=TCNT1/116;         // Cm로 변경 //
}
int main(void)
{
	clcd_port_init();//CPU초기화
	clcd_init_8bit();//LCD초기화
	
	DDRD=1;                  // PD0 ouput Trigger, PC1 input Echo
	DDRB=0xFF;               // LED out
	TCCR1A=0; TCCR1B=8;      // CTC mode
	while(1)
	{
		Trigger_1; _delay_us(10); Trigger_0;    // 10uS
		getEcho();
		if     (range< 5)
		{ 
			clcd_str("range < 50cm");
			_delay_ms(100);
			clcd_init_8bit();
		}
		else if(range<10)
		{
			clcd_str("range < 1m");
			 _delay_ms(100);
			clcd_init_8bit();
		 }
		else if(range<15)
		{
			 clcd_str("range < 1.5m");
			 _delay_ms(100);
			 clcd_init_8bit();
	    }
		else if(range<20)
		{
			 clcd_str("range < 2m");
			 _delay_ms(100);
			 clcd_init_8bit();
		 }
		else if(range<25)
		{
			 clcd_str("range < 2.5m");
			 _delay_ms(100);
			 clcd_init_8bit();
		 }
		else if(range<30)
		{
			 clcd_str("range < 3m");
			 _delay_ms(100);
			 clcd_init_8bit();
		 }
		else if(range<35)
		{
			 clcd_str("range < 3.5m");
			 _delay_ms(100);
			 clcd_init_8bit();
		 }
		else if(range<40)
		{
			 clcd_str("range < 4m");
			 _delay_ms(100);
			 clcd_init_8bit();
		 }
		else             
		{ 
			clcd_str("range < 4.5m");
			_delay_ms(100);
			clcd_init_8bit();
		}
		_delay_ms(100);
	}
}