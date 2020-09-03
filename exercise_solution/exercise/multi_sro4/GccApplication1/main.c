#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "clcd_D8.h"


//
#define Trig1_ON PORTB|=1 //트리거1
#define Trig2_ON PORTB|=2 //트리거2
#define Trig3_ON PORTB|=4 //트리거3
#define Trig4_ON PORTB|=8 //트리거4
//
#define Trig1_OFF PORTB&=~1 //트리거1
#define Trig2_OFF PORTB&=~2 //트리거2
#define Trig3_OFF PORTB&=~4 //트리거3
#define Trig4_OFF PORTB&=~8 //트리거4
//
char s[30];
unsigned int range_I, range[4];
float range_F;
//
char temp[3]={'0','0','0'};
//
void getEcho(int ch){ // ch=0~3
	while(!(PINB&(0x10<<ch)));  // Wait for echo pin to go high
	TCNT1=0x00; TCCR1B=0x02;    // 1:8 prescaler = 0.5us
	while(PINB&(0x10<<ch));     // Wait for echo pin to go low
	TCCR1B=0x08; range_I=TCNT1; // the range in CM
	range_F=(float)range_I;
	range_F/=11.6; // mm
	range[ch]=(unsigned int)range_F; // range[ch]에 저장
}
//


//
int main(void){
	
	//char sample="exercise";
	DDRB=0x0F;  // PB0~3 ouput Trigger, PB4~7 input Echo
	DDRD=0x0F;

	TCCR1B=0x08;  // Set timer up in CTC mode
	_delay_ms(100);
	
	clcd_port_init();//CPU초기화
	clcd_init_8bit();//LCD초기화
	PORTD = 0x07;
	//   init(); // lcd 초기화 함수
	while(1){
		//PORTD = 0x07;
		_delay_ms(25); Trig1_ON; _delay_us(10); Trig1_OFF; getEcho(0);
		if (range[0]<50){PORTD = 0b00000000; /*_delay_us(0.01);*/}
		else if( range[0]> 50) {PORTD = 0b00000001; /*_delay_ms(100);*/}
		
		_delay_ms(25); Trig2_ON; _delay_us(10); Trig2_OFF; getEcho(1);
		if (range[1]<50){PORTD = 0b00000000; /*_delay_us(0.01);*/}
		else if( range[1]> 50) {PORTD = 0b00000010;/*_delay_ms(100);*/}
		
		_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
		if (range[2]<50){PORTD = 0b00000000;/* _delay_us(0.01);*/}
		else if( range[2]> 50) {PORTD = 0b00000100;/* _delay_ms(100);*/}
	
		
	}
}