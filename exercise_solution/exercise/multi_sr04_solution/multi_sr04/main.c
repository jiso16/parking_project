#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>



//
#define Trig1_ON PORTB|=1 //트리거1
#define Trig2_ON PORTB|=2 //트리거2
#define Trig3_ON PORTB|=4 //트리거3
//#define Trig4_ON PORTB|=8 //트리거4
//
#define Trig1_OFF PORTB&=~1 //트리거1
#define Trig2_OFF PORTB&=~2 //트리거2
#define Trig3_OFF PORTB&=~4 //트리거3
//#define Trig4_OFF PORTB&=~8 //트리거4
//
char s[30];
unsigned int range_I, range[4];
float range_F;
//
char temp[3]={'0','0','0'};
//
void getEcho(int ch){ // ch=0~3
	while(!(PINB&(0x40<<ch)));  // Wait for echo pin to go high
	TCNT1=0x00; TCCR1B=0x02;    // 1:8 prescaler = 0.5us
	while(PINB&(0x40<<ch));     // Wait for echo pin to go low
	TCCR1B=0x08; range_I=TCNT1; // the range in CM
	range_F=(float)range_I;
	range_F/=11.6; // mm
	range[ch]=(unsigned int)range_F; // range[ch]에 저장
}
//


//
int main(void){
	DDRA = 0xc0;
	DDRC = 0xff;


	DDRB=0x0F;  // PB0~3 ouput Trigger, PB4~7 input Echo


	TCCR1B=0x08;  // Set timer up in CTC mode
	_delay_ms(100);
	//    init(); // lcd 초기화 함수
	while(1){
		_delay_ms(25); Trig1_ON; _delay_ms(10); Trig1_OFF; getEcho(0); PORTA = 0B00000001;
		_delay_ms(25); Trig2_ON; _delay_ms(10); Trig2_OFF; getEcho(1); PORTA = 0B00000010;
		_delay_ms(25); Trig3_ON; _delay_ms(10); Trig3_OFF; getEcho(2); PORTA = 0B00000100;
		//_delay_ms(25); Trig4_ON; _delay_us(10); Trig4_OFF; getEcho(3);
		//
		
		//
		//        lcd_inst(0x01);  _delay_ms(10);
		//        lcd_strout(0x00+i,temp[i]); // lcd 문자열 함수 이름으로 바꾸세요
	}
}

