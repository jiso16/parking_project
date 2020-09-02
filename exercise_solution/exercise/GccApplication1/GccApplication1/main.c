#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "clcd_D8.h"


#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
//
#define trig1_1 PORTB|=1  // PA0, srf04-1 트리거
#define trig1_0 PORTB&=~1 // PA0, srf04-1 트리거
#define echo1   (PORTB&2)  // PA1, srf04-1 에코
//
#define trig2_1 PORTB|=4  // PA2, srf04-2 트리거
#define trig2_0 PORTB&=~4 // PA2, srf04-2 트리거
#define echo2   (PORTB&8)  // PA3, srf04-2 에코


//
unsigned int  cnt1,cnt2;

unsigned int mode = 0;

void getEcho(void){
	
		clcd_str("sensor test2");
		_delay_ms(50);
		clcd_init_8bit();//LCD초기화
	
		trig1_1;       _delay_us(10); trig1_0; //트리거1
		
		clcd_str("sensor test3");
		_delay_ms(50);
		clcd_init_8bit();//LCD초기화
		
		
		while(!echo1); TCNT1=0;       TCCR1B=2;
		while( echo1); TCCR1B=0;      cnt1=TCNT1/116;
		_delay_ms(50);
		
		//
		trig2_1;       _delay_us(10); trig2_0; //트리거2
		while(!echo2); TCNT1=0;       TCCR1B=2;
		while( echo2); TCCR1B=0;      cnt2=TCNT1/116;
		_delay_ms(50);      // Cm로 변경 //
		
		clcd_str("sensor test4");
		_delay_ms(50);
		clcd_init_8bit();//LCD초기화
		
		 //if(cnt1<50)
		 //{mode=1; }
		 //else if(cnt2<50)
		 //{mode = 2; }
}


//
int main(void){
	
	clcd_port_init();//CPU초기화
	clcd_init_8bit();//LCD초기화
	
	clcd_str("sensor test");
	_delay_ms(50);
	clcd_init_8bit();//LCD초기화
	
	//DDRD=1;
	DDRA=0x05;     // PB0,2 ouput Trigger, PB1,3 input Echo


	TCCR1A=0; TCCR1B=8;
	
	while(1)
	{
		trig1_1; _delay_us(10); trig1_0;
		getEcho();
		
		trig2_1; _delay_us(10); trig2_0;
		getEcho();
		
		if(cnt1<50)
		{
			clcd_str("sensor1");
			_delay_ms(50);
			clcd_init_8bit();//LCD초기화
		}
		if(cnt2 <50)
		{
			clcd_position(1,0);
			clcd_str("sensor2");
			_delay_ms(50);
			clcd_init_8bit();//LCD초기화
		}
	}
	
}
