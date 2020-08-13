#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"


char KeyScan();
void check_PW();

char KeyBuf[30];
char buf[10];
char inputPassword [10];
char match [10]="1234";

int main()
{
	char key;

	clcd_port_init();
	clcd_init_8bit();
	
	clcd_str("Program Start");
	clcd_position(1,0);
	clcd_str("Enter the PW");
	
	while(1)
	{
		key = KeyScan();
		if(key== 0xFF)
		{
			continue;
		}
		else
		{
			//clcd_init_8bit();
			//sprintf(buf,"%c", key);
			//clcd_str(buf);
			for (int i = 0; i< 4; i++)
			{
				buf[i] = inputPassword[i];
			}
			//clcd_str(buf);
		}
		check_PW();
	}
}

void check_PW()
{
	int isMatch = 1;
	for (int j = 0; j<4; j++)
	{
		if(inputPassword[j] != match[j])
		{
			isMatch = 0;
		}
	}
	if(isMatch == 1)
	{
		clcd_str("Okay");
	}
	else
	{
		clcd_str("error");
	}
}

char KeyScan()
{

	char KeyBuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택
	_delay_ms(3);
	if((PINE&0x10)==0)KeyBuf='1';
	if((PINE&0x20)==0)KeyBuf='2';
	if((PINE&0x40)==0)KeyBuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	_delay_ms(3);
	if((PINE&0x10)==0)KeyBuf='4';
	if((PINE&0x20)==0)KeyBuf='5';
	if((PINE&0x40)==0)KeyBuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	_delay_ms(3);
	if((PINE&0x10)==0)KeyBuf='7';
	if((PINE&0x20)==0)KeyBuf='8';
	if((PINE&0x40)==0)KeyBuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	_delay_ms(3);
	if((PINE&0x10)==0)KeyBuf='*';
	if((PINE&0x20)==0)KeyBuf='0';
	if((PINE&0x40)==0)KeyBuf='#';
	PORTE|=8; // 4번째 줄 해제
	
	return KeyBuf;
}