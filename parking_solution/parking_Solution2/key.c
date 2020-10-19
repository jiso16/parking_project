#include "parking.h"

char key;
char keybuf[30];
char buf[10];

char KeyScan()
{

	char keybuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택
	_delay_ms(30);
	if((PINE&0x10)==0)keybuf='1';
	if((PINE&0x20)==0)keybuf='2';
	if((PINE&0x40)==0)keybuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	_delay_ms(30);
	if((PINE&0x10)==0)keybuf='4';
	if((PINE&0x20)==0)keybuf='5';
	if((PINE&0x40)==0)keybuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	_delay_ms(30);
	if((PINE&0x10)==0)keybuf='7';
	if((PINE&0x20)==0)keybuf='8';
	if((PINE&0x40)==0)keybuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	_delay_ms(30);
	if((PINE&0x10)==0)keybuf='*';
	if((PINE&0x20)==0)keybuf='0';
	if((PINE&0x40)==0)keybuf='#';
	PORTE|=8; // 4번째 줄 해제
	
	return keybuf;
}