#define  F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//
volatile unsigned int  buf[3],dist[3],start=0,end=0;
volatile unsigned char cnt=0,flag[3]={0,0,0};
//
//에코핀
ISR(INT0_vect) // 에코 PD0
{ 
	if(EICRA==0x03)
		start=TCNT3; 
	else
	{
		end=TCNT3;
		buf[0]=end-start;
		EIMSK=0;
		flag[0]=1;
		if (dist[0]<0.5)
		{
			PORTF &= ~0x01;
		}
		else
		{
			PORTF |= 0x01;
		}
	} 
	EICRA^=0x01;
}
ISR(INT1_vect) // 에코 PD1
{
	if(EICRA==0x0C)
		start=TCNT3;
	else
	{
		end=TCNT3;
		buf[1]=end-start;
		EIMSK=0;
		flag[1]=1;
		if (dist[1]<0.5)
		{
			PORTF &= ~0x02;			
		}
		else
		{
			PORTF |= 0x02;
		}
	}
	EICRA^=0x04;
}
ISR(INT2_vect)  // 에코 PD2
{ 
	if(EICRA==0x30)
		start=TCNT3; 
	else
	{ 
		end=TCNT3; 
		buf[2]=end-start;
		EIMSK=0;
		flag[2]=1;
		if (dist[2]<0.5)
		{
			PORTF &= ~0x04;
		}
		else
		{
			PORTF |= 0x04;
		}
	} 
	EICRA^=0x10;
}

//트리거
ISR(TIMER3_COMPA_vect)
{
	switch(cnt){
		case 0: 
		PORTD|=0x10; 
		_delay_us(10); 
		PORTD&=~0x10; 
		EICRA=0x03; 
		EICRB=0x00; 
		EIFR=0xFF; 
		EIMSK=0x01; 
		break;
		
		case 1: 
		PORTD|=0x20; 
		_delay_us(10); 
		PORTD&=~0x20; 
		EICRA=0x0C; 
		EICRB=0x00; 
		EIFR=0xFF;
		EIMSK=0x02; 
		break;
		
		case 2: 
		PORTD|=0x40; 
		_delay_us(10); 
		PORTD&=~0x40; 
		EICRA=0x30; 
		EICRB=0x00; 
		EIFR=0xFF; 
		EIMSK=0x04; 
		break;
	}
	if(++cnt>3)cnt=0;
}
//
int main(void){
	DDRD=0x70; // 트리거
	DDRF=0x07;
	TCCR3B=0x0C; 
	OCR3A=3124; 
	ETIMSK=0x10; //16000000/256/(1+ 3124)=20Hz=50ms
	sei();//SREG=0x80;
	while(1)
	{
		if(flag[0])
		{ 
			flag[0]=0;
			dist[0]=(int)((float)buf[0]/14.5);
		}
		if(flag[1])
		{ 
			flag[1]=0; 
			dist[1]=(int)((float)buf[1]/14.5);
		}
		if(flag[2])
		{ 
			flag[2]=0;
			dist[2]=(int)((float)buf[2]/14.5);
		}
	}
}
