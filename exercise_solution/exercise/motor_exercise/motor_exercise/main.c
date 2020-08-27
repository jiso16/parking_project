#include <avr/io.h> //16MHz
#define  F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
//
void RC_Motor(int angle){ // angle : -90도 ~ +90도
	int i;
	if(angle<-90)angle=-90;
	if(angle> 90)angle= 90;
	i=(angle)*18 + 3000;
	OCR1A=i; //PB5
}
//
int main(void){
	//RC서보모터
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; // FAST PWM
	TCCR1B=0x1A; // 8분주=0.5usec
	OCR1A=3000;  // 1500usec=0도
	ICR1=39999;  // 0.5usec*40000=20000usec=50Hz
	while(1){
		RC_Motor(-90); _delay_ms(1000);
		RC_Motor(  0); _delay_ms(1000);
		RC_Motor( 90); _delay_ms(1000);
		RC_Motor(  0); _delay_ms(1000);
	}
}