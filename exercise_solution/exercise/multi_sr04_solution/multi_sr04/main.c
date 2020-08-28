#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "clcd_D8.h"


//
#define Trig1_ON PORTD|=1 //트리거1
#define Trig2_ON PORTD|=2 //트리거2
#define Trig3_ON PORTD|=4 //트리거3
//#define Trig4_ON PORTB|=8 //트리거4
//
#define Trig1_OFF PORTD&=~1 //트리거1
#define Trig2_OFF PORTD&=~2 //트리거2
#define Trig3_OFF PORTD&=~4 //트리거3
//#define Trig4_OFF PORTB&=~8 //트리거4
//
char s[30];
unsigned int range_I, range[3];
float range_F;
//
char temp[3]={'0','0','0'};
//
void getEcho(int ch)
{ // ch=0~3
	while(!(PORTD&(0x40<<ch)));  // Wait for echo pin to go high
	TCNT1=0x00; TCCR1B=0x02;    // 1:8 prescaler = 0.5us
	while(PORTD&(0x40<<ch));     // Wait for echo pin to go low
	TCCR1B=0x08; range_I=TCNT1; // the range in CM
	range_F=(float)range_I;
	range_F/=11.6; // mm
	range[ch]=(unsigned int)range_F; // range[ch]에 저장
}
//


//
int main(void)
{

	//int i  = 0;
	clcd_port_init();//CPU초기화
	clcd_init_8bit();//LCD초기화
	
	DDRD=0x0F;  // PB0~3 ouput Trigger, PB4~7 input Echo


	TCCR1B=0x08;  // Set timer up in CTC mode
	_delay_ms(100);
	//    init(); // lcd 초기화 함수
	while(1)
	{
		_delay_ms(25); Trig1_ON; _delay_ms(10); Trig1_OFF; getEcho(0); clcd_position(0,1); clcd_str("1"); _delay_ms(100); clcd_init_8bit();
		_delay_ms(25); Trig2_ON; _delay_ms(10); Trig2_OFF; getEcho(1); clcd_position(0,3); clcd_str("2"); _delay_ms(100); clcd_init_8bit();
		_delay_ms(25); Trig3_ON; _delay_ms(10); Trig3_OFF; getEcho(2); clcd_position(0,5); clcd_str("3"); _delay_ms(100); clcd_init_8bit();
		//_delay_ms(25); Trig4_ON; _delay_us(10); Trig4_OFF; getEcho(3);
		//
		 //sprintf(temp,"1:%3d 2:%3d 3:%3d",range[0],range[1],range[2]);
		//
		//        lcd_inst(0x01);  _delay_ms(10);
		//clcd_str(temp); // lcd 문자열 함수 이름으로 바꾸세요
		//i++;
		//_delay_ms(50);
		//clcd_init_8bit();//LCD초기화

	}
}

