#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"
#define bufferSize 4

char KeyScan();
void checkPassword();
void putValueToBuffer(char value);
void clearBuffer();
void enterPassword();
int isBufferEmpty();
int isMatchKey(int mode);

enum WindowPosition { OPEN, INIT, Admin_1, Admin_2, User_1, User_PW} currentPage ;
char buf[bufferSize];
char key;
char adminPw[4]={49,50,51,52};

int main()
{
	//int num=1;
	//char buf[30],key;
	//char area1Pw[4]={49,50,51,52};
	//char area2Pw[4]={49,50,51,52};
	//char area3Pw[4]={49,50,51,52};
	//char area4Pw[4]={49,50,51,52};
	
		
	
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_position(0, 0);
	clcd_str("Parking System");
	_delay_ms(200);
	clcd_init_8bit();
		
	while(1)
	{
		
		_delay_us(50);	
		key = KeyScan();
		
		if(key == 0xFF && currentPage != OPEN)
		{
			continue;
		}
		else 
		{
			switch(currentPage)
			{
				case OPEN :
				{
					clcd_str("Select the mode");
					_delay_ms(200);
					clcd_init_8bit();
					clcd_str("1) Admin mode");
					clcd_position(1, 0);
					clcd_str("2) Visitor mode");
					currentPage = INIT;
					break;
				}
				case INIT :
				{
					clcd_init_8bit();
					clcd_str(key);
					_delay_ms(300);
					clcd_init_8bit();
		
					
					if(isMatchKey(49) == 1)
					{
						//관리자모드 진입
						currentPage = Admin_1;
						clcd_str("Admin mode.");
						clcd_position(1, 0);
						clcd_str("Enter the PW");
						enterPassword();
						checkPassword();
						
					}
					else if (isMatchKey(50))
					{
						//유저모드 진입
						currentPage = User_1;
						clcd_str("Visitor mode.");
						clcd_position(1, 0);
						clcd_str("Enter your area");
					}
					else
					{
						currentPage = INIT;
						clcd_str("Choose 1 or 2");
						_delay_ms(300);
						clcd_init_8bit();
					}
					break;
					
				}
				case Admin_1 :
				{
					
					clcd_str("aaaaaa");
					_delay_ms(300);
					clcd_init_8bit();
					if (isMatchKey(49))
					{
						currentPage = Admin_2;
						clcd_position(1, 0);
						clcd_str("PW is Correct!");
						_delay_ms(300);
						clcd_init_8bit();	
										
					}
					else 
					{
						currentPage = INIT;
						clcd_position(1, 0);
						clcd_str("Wrong PW");
						_delay_ms(300);
						clcd_init_8bit();
					}
					_delay_ms(300);
					clcd_init_8bit();
					break;
				}
				
				case User_1 :
				{
					if(isMatchKey(49))
					{
						clcd_str("Area 1");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
						
					}
					else if (isMatchKey(50))
					{
						clcd_str("Area 2");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
					}
					else if (isMatchKey(51))
					{
						clcd_str("Area 3");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
					}
					else if (isMatchKey(52))
					{
						clcd_str("Area 4");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
					}
					else
					{
						clcd_str("Wrong Space");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage = INIT;

					}
					
					break;
					
				}
				case Admin_2 :
				{
					break;
				}
				case User_PW :
				{
					//if
					break;
				}
				
			}
				
			
		}
	}
	return 0;	
}

void checkPassword(){
	int isMatch = 1;
	for(int i=0; i<4; i++)
	{
		if(buf[i] != adminPw[i]){
			isMatch = 0;
		}		
	}
	
	if(isMatch == 1)
	{
		currentPage = Admin_1;
	}
	else
	{
		currentPage = OPEN;
	}
	// buf 내용을 가져와서 ADMIN 비번이랑 비교한다
	// 맞으면 어드민 모드, 아니면 1,2 번 선택화면으로 보낸다., 비번이 틀렸습니다. 	
}

void putValueToBuffer(char value){
	for(int i = 0; i < bufferSize; i ++){
		if(buf[i] == '\0'){
			buf[i] = value;
			return;
		}
	}
}

void clearBuffer(){
	for(int i = 0; i < bufferSize; i ++){		
		buf[i] = '\0';	
	}
}

int isBufferEmpty(){
	for(int i = 0; i < bufferSize; i ++){
		if(buf[i] != '\0'){
			return 0;
		}
	}
	
	return 1;
}

int isMatchKey(int mode){
	if(key == mode){
		return 1;
	}else{
		return 0;
	}
}

void enterPassword(){
	int isComplete = 0;
	while(isComplete != 1){
		char key = KeyScan();
		if(key !=  '\0'){
			putValueToBuffer(key);
			clcd_init_8bit();
			clcd_str(buf);
		}
		if(buf[3] != '\0'){
			isComplete = 1;
		}
	}
}

char KeyScan()
{
	//char KeyBuf[30];
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
	
	return KeyBuf;
}