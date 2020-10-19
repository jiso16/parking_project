#include "parking.h"

//초음파센서 변수
volatile unsigned int  buf2[3],dist[3],start,end;
volatile unsigned char cnt,flag[3];


ISR(INT0_vect) // 에코 PD0
{
	if(EICRA==0x03)
	start=TCNT3;
	else
	{
		end=TCNT3;
		buf2[0]=end-start;
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
		buf2[1]=end-start;
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
		buf2[2]=end-start;
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

ISR(TIMER3_COMPA_vect)
{
	switch(cnt)
	{
		case 0:
		PORTD|=0x10;
		_delay_us(10);
		PORTD&=~0x10;
		EICRA=0x03; //인터럽트 0~3 설정
		EIFR=0xFF;  // 인터럽트 클리어 해주는 레지스터
		EIMSK=0x01; // 개별적 인터럽트 허용 레지스터
		break;
		
		case 1:
		PORTD|=0x20;
		_delay_us(10);
		PORTD&=~0x20;
		EICRA=0x0C;
		EIFR=0xFF;
		EIMSK=0x02;
		break;
		
		case 2:
		PORTD|=0x40;
		_delay_us(10);
		PORTD&=~0x40;
		EICRA=0x30;
		EIFR=0xFF;
		EIMSK=0x04;
		break;
	}
	if(++cnt>3)
	cnt=0;
}