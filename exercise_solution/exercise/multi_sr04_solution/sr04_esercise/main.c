#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


#define Trig1_ON PORTD|=1 //트리거1
#define Trig2_ON PORTD|=2 //트리거2
#define Trig3_ON PORTD|=4 //트리거3

#define Trig1_OFF PORTD&=~1 //트리거1
#define Trig2_OFF PORTD&=~2 //트리거2
#define Trig3_OFF PORTD&=~4 //트리거3

char s[30];
unsigned int range_I, range[4];
float range_F;

char temp[3]={'0','0','0'};

void getEcho(int ch){ // ch=0~3
	while(!(PIND&(0x10<<ch)));  // Wait for echo pin to go high
	TCNT1=0x00; TCCR1B=0x02;    // 1:8 prescaler = 0.5us
	while(PIND&(0x10<<ch));     // Wait for echo pin to go low
	TCCR1B=0x08; range_I=TCNT1; // the range in CM
	range_F=(float)range_I;
	range_F/=11.6; // mm
	range[ch]=(unsigned int)range_F; // range[ch]에 저장
}
//


//
int main(void)
{
	
	DDRD=0x0F;  // PD0~3 ouput Trigger, PD4~7 input Echo
	DDRF=0x07;  //led output

	TCCR1B=0x08;  // Set timer up in CTC mode
	_delay_ms(100);
	
	while(1)
	{
		_delay_ms(25); Trig1_ON; _delay_us(10); Trig1_OFF; getEcho(0);
		
		if ((range[0]<50)) // range[0]이 범위 안일 때
		{
			_delay_ms(25); Trig2_ON; _delay_us(10); Trig2_OFF; getEcho(1);
			
			
			if ((range[0]<50) && (range[1]<50))
			{
				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
				
				if ((range[0]<50) && (range[1]<50) && (range[2]<50))
				{
					PORTF = 0b00000000;
				}
				else if((range[0]<50) && (range[1]<50) && (range[2]>50))
				{
					PORTF = 0b00000100;
				}
			}
			else if((range[0]<50) && (range[1]>50))
			{
				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
				
				if ((range[0]<50) && (range[1]>50) && (range[2]<50))
				{
					PORTF = 0b00000010;
				}
				else if((range[0]<50) && (range[1]>50) && (range[2]>50))
				{
					PORTF = 0b00000110;
				}
			
			}
		}
		else if(range[0]>50) // range[0]이 범위 밖일 때
		{			
			_delay_ms(25); Trig2_ON; _delay_us(10); Trig2_OFF; getEcho(1);
			if((range[0]>50) && (range[1]<50))
			{
				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
				if ((range[0]>50) && (range[1]<50) && (range[2]<50))
				{
					PORTF = 0b00000001;
				}
				else if ((range[0]>50) && (range[1]<50) && (range[2]>50))
				{
					PORTF = 0b00000101;
				}
			}
			else if((range[0]>50) && (range[1]>50))
			{
				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
				if ((range[0]>50) && (range[1]>50) && (range[2]<50))
				{
					PORTF = 0b00000011;
				}
				else if ((range[0]>50) && (range[1]>50) && (range[2]>50))
				{
					PORTF = 0b00000111;
				}
			}
			
		}
		
	}
}