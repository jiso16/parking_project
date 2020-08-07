#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"

enum WindowPosition { INIT, Admin_1, Admin_2, User_1, User_PW} currentPage ;

char KeyScan(void);
int key_input();

int main()
{
	//int num=1;
	char buf[30],key;
	//char area1Pw[4]={49,50,51,52};
	//char area2Pw[4]={49,50,51,52};
	//char area3Pw[4]={49,50,51,52};
	//char area4Pw[4]={49,50,51,52};
	//char adminPw[4]={49,50,51,52};
		
	
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_position(0, 0);
	clcd_str("Parking System");
	_delay_ms(300);
	clcd_init_8bit();
	
	clcd_str("1) Admin mode");
	clcd_position(1, 0);
	clcd_str("2) Visitor mode");
	_delay_ms(300);
	clcd_init_8bit();
	clcd_str("Select the mode");
	clcd_position(1, 0);
	clcd_str("Press the number");
	_delay_ms(300);
	clcd_init_8bit();

	while(1)
	{
		
		_delay_us(50);
		
		key=KeyScan();
		for(int i=0; i<1; i++)
		{
			if(key!=0xFF )
			{
				//clcd_position(0,i);
				sprintf(buf,"Num: %c",key);
				clcd_str(buf);			
			}
			_delay_ms(70);
			
		}
		clcd_init_8bit();
		if( key == 0)
		{
			continue;
		}
		else 
		{
			switch(currentPage)
			{
				case INIT :
				{
					if(key == 49)
					{
						//관리자모드 진입
						currentPage = Admin_1;
						clcd_str("Admin mode.");
						clcd_position(1, 0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						//num = 4;
						
					}
					else if (key == 50)
					{
						//유저모드 진입
						currentPage = User_1;
						clcd_str("Visitor mode.");
						clcd_position(1, 0);
						clcd_str("Enter your area");
						_delay_ms(300);
						clcd_init_8bit();
					}
					else
					{
						clcd_str("Choose 1 or 2");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage = INIT;
					}
					
				}
				case Admin_1 :
				{
					
					clcd_str("aaaaaa");
					_delay_ms(300);
					clcd_init_8bit();
					if (key==49505152)
					{
						currentPage = Admin_2;
						clcd_position(1, 0);
						clcd_str("PW is Correct!");
						_delay_ms(300);
						clcd_init_8bit();	
										
					}
					else 
					{
						
					}
					_delay_ms(300);
					clcd_init_8bit();
				}
				case User_1 :
				{
					if(key == 49)
					{
						clcd_str("Area 1");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
						
					}
					else if (key==50)
					{
						clcd_str("Area 2");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
					}
					else if (key==51)
					{
						clcd_str("Area 3");
						clcd_position(1,0);
						clcd_str("Enter the PW");
						_delay_ms(300);
						clcd_init_8bit();
						currentPage= User_PW;
					}
					else if (key==52)
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
					
					
					
				}
				case Admin_2 :
				{
					
				}
				case User_PW :
				{
					//if
				}
				
			}
				
			
		}
	}
	return 0;	
}

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

int key_input( )
{
	char buf[30], key;
	//clcd_port_init();
	//clcd_init_8bit();
	
	key=KeyScan();
	if(key!=0xFF )
	{
		sprintf(buf,"mode: %c",key);
		clcd_str(buf);
		
	}
	_delay_ms(500);
	clcd_init_8bit();
	return key;
}