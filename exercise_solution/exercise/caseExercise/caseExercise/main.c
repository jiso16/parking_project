#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"

enum WindowPosition { OPEN, MODE1, MODE2} currentPage ;

char KeyScan();
void check_PW();
void modeInput();


char key;
char KeyBuf[30];
char buf[10];
char inputPassword [10];

int main()
{
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_str("Enter the Number");
	
	while(1)
	{
		key = KeyScan();
		
		if(key == 0xFF)
		{
			continue;
		}
		else
		{
			clcd_init_8bit();
			sprintf(buf,"%c",key);
			clcd_str(buf);
			
			switch(currentPage)
			{
				case OPEN:
				{
					clcd_init_8bit();
					
					modeInput();
					break;
				}
				case MODE1:
				{
					clcd_init_8bit();
					clcd_str("This is MODE1");
					_delay_ms(200);
					break;
				}
				case MODE2:
				{
					clcd_init_8bit();
					clcd_str("This is Mode2");
					_delay_ms(200);
					break;
				}
				
			}
		}
	}
}

void modeInput() // 관리자모드 비번 입력
{
	clcd_init_8bit();
	int i=0;
	clcd_str("Enter the mode");
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,0);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			inputPassword[0] = key;
			if(strcmp(buf,"1")==0)
			{
				currentPage = MODE1;
				break;
			}
			else if(strcmp( buf, "2")==0)
			{
				currentPage = MODE2;
				break;
			}
		}
	}
}
void check_PW() // 관리자 모드 비번 확인
{
	clcd_init_8bit();

	if(strcmp(inputPassword[0],"1")==0)
	{
		clcd_str("mode 1");
		_delay_ms(100);
		currentPage = MODE1;
	}
	else if(strcmp(inputPassword[0], "2")==0)
	{
		clcd_str("mode 1");
		_delay_ms(100);
		currentPage = MODE2;
	}
	inputPassword[10] = '\0';	
}
char KeyScan()
{

	char KeyBuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택 
	_delay_ms(2);
	if((PINE&0x10)==0)KeyBuf='1';
	if((PINE&0x20)==0)KeyBuf='2';
	if((PINE&0x40)==0)KeyBuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)KeyBuf='4';
	if((PINE&0x20)==0)KeyBuf='5';
	if((PINE&0x40)==0)KeyBuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)KeyBuf='7';
	if((PINE&0x20)==0)KeyBuf='8';
	if((PINE&0x40)==0)KeyBuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)KeyBuf='*';
	if((PINE&0x20)==0)KeyBuf='0';
	if((PINE&0x40)==0)KeyBuf='#';
	PORTE|=8; // 4번째 줄 해제
	
	return KeyBuf;
}