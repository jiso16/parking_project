#include<avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
//
#define Trigger_1       PORTC|=1  //초음파 트리거
#define Trigger_0       PORTC&=~1 //초음파 트리거
#define Echo            (PINC&2)  //초음파 에코
//
unsigned int range;
//
void getEcho(void){
	while(!Echo);            // high가 될때까지 대기 //
	TCNT1=0; TCCR1B=2;       // 카운터 시작, 8분주 = 0.5us //
	while(Echo);             // low가 될때까지 대기 //
	TCCR1B=8;                // 카운터 정지 //
	range=TCNT1/116;         // Cm로 변경 //
}
int main(void){
	DDRC=1;                  // PC0 ouput Trigger, PC1 input Echo
	DDRB=0xFF;               // LED out
	TCCR1A=0; TCCR1B=8;      // CTC mode
	while(1){
		Trigger_1; _delay_us(10); Trigger_0;    // 10uS
		getEcho();
		if     (range< 5){ PORTB=0b00000000; }
		else if(range<10){ PORTB=0b00000001; }
		else if(range<15){ PORTB=0b00000011; }
		else if(range<20){ PORTB=0b00000111; }
		else if(range<25){ PORTB=0b00001111; }
		else if(range<30){ PORTB=0b00011111; }
		else if(range<35){ PORTB=0b00100000; }
		else if(range<40){ PORTB=0b01000000; }
		else             { PORTB=0b10000000; }
		_delay_ms(50);
	}
}