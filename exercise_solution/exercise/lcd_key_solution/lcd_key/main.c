#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//#include <stdlib.h> 
#include "clcd_D8.h"
//
char KeyScan(void)
{
	char KeyBuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택
	_delay_us(5);
	if((PINE&0x10)==0)KeyBuf='1';
	if((PINE&0x20)==0)KeyBuf='2';
	if((PINE&0x40)==0)KeyBuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	_delay_us(5);
	if((PINE&0x10)==0)KeyBuf='4';
	if((PINE&0x20)==0)KeyBuf='5';
	if((PINE&0x40)==0)KeyBuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	_delay_us(5);
	if((PINE&0x10)==0)KeyBuf='7';
	if((PINE&0x20)==0)KeyBuf='8';
	if((PINE&0x40)==0)KeyBuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	_delay_us(5);
	if((PINE&0x10)==0)KeyBuf='*';
	if((PINE&0x20)==0)KeyBuf='0';
	if((PINE&0x40)==0)KeyBuf='#';
	PORTE|=8; // 4번째 줄 해제

	return KeyBuf; // Key 없으면 0xFF 리턴
}

int main(void)
{
	char buf[30],key;
	int input = 0;
	int i=0;
	clcd_port_init();
	clcd_init_8bit();
	while(1)
	{
		key=KeyScan();
		input = atoi(key); 
		clcd_position(0,0);
		if(key!=0xFF )
		{
			clcd_position(0,i);
			sprintf(buf,"%d",input);
			clcd_str(buf);
			i++;
			if(i==16)i=0;
		}
		_delay_ms(20);
	}
}