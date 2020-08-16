#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"

char KeyScan();
void PwInput();
void check_PW();
void userPwInput ();
void checkUserPW();

enum WindowPosition { OPEN, INIT, Admin_1, Admin_2, User_1, User_PW} currentPage ;

char key;
char KeyBuf[30];
char buf[10];
char inputPassword [10];
char initalPw [10]="1234";
//char area_PW [5][10]= {"0","1234","1234","1234","1234"};
char area1_PW [10]= "1234";
//char area3_PW [10]= "1234";
//char area4_PW [10]= "1234"; 

int main()
{
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_position(0, 0);
	clcd_str("Parking System");
	_delay_ms(200);
	clcd_init_8bit();
	
	while(1)
	{
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
					clcd_init_8bit();
					clcd_str("Select the mode");
					_delay_ms(200);
					clcd_init_8bit();
					clcd_str("1) Admin mode");
					clcd_position(1, 0);
					clcd_str("2) Visitor mode");
					currentPage = INIT;
					break;
				}
				
				case INIT:
				{
					clcd_init_8bit();
					sprintf(buf,"%c",key);
					clcd_str(buf);
					_delay_ms(100);
					clcd_init_8bit();
					
					
					if(strcmp(buf,"1")==0)
					{
						//관리자모드 진입
						//currentPage = Admin_1;
						clcd_str("Admin mode.");
						PwInput();
						
					}
					else if (strcmp (buf,"2")==0)
					{
						//유저모드 진입
						currentPage = User_1;
						clcd_str("Visitor mode.");
						clcd_position(1, 0);
						clcd_str("Enter Your Area");
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
					sprintf(buf,"%c",key);
					clcd_str(buf);
					_delay_ms(100);
					clcd_init_8bit();
					
					if (strcmp(buf,"1")==0)
					{
						clcd_str("Area 1");	
						changePw1(buf);
										
					}
					else if(strcmp(buf,"2")==0)
					{
						
					}
					else if(strcmp(buf,"3")==0)
					{
						
					}
					else if(strcmp(buf,"4")==0)
					{
						
					}
					else
					{
						
					}
					break;
				}
				case User_1 :
				{
					clcd_init_8bit();
					sprintf(buf,"%c",key);
					clcd_str(buf);
					_delay_ms(100);
					clcd_init_8bit();
					
					if(strcmp(buf,"1")==0)
					{
						clcd_str("Area 1");
						_delay_ms(200);
						clcd_init_8bit();
						userPwInput();						
					}
					else if (strcmp(buf,"2")==0)
					{
						clcd_str("Area 2");
						_delay_ms(200);
						clcd_init_8bit();
						userPwInput();
					}
					else if (strcmp(buf,"3")==0)
					{
						clcd_str("Area 3");
						_delay_ms(200);
						clcd_init_8bit();
						userPwInput();
					}
					else if (strcmp(buf,"4")==0)
					{
						clcd_str("Area 4");
						_delay_ms(200);
						clcd_init_8bit();
						userPwInput();
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
			}
		}
	}
}

void PwInput() // 관리자모드 비번 입력
{
	clcd_init_8bit();
	clcd_str("Enter the PW");
	int i = 0;
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			inputPassword[i] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				check_PW();
				break;
			}
		}
	}
}

void check_PW() // 관리자 모드 비번 확인
{
	clcd_init_8bit();
	int isMatch = 1;
	for (int j = 0; j<4; j++)
	{
		if(inputPassword[j] != initalPw[j])
		{
			isMatch = 0;
		}
	}
	if(isMatch == 1)
	{
		clcd_str("Okay");
		_delay_ms(100);
		clcd_init_8bit();
		clcd_str("Which position");
		clcd_position(1,0);
		clcd_str("change the PW?");
		currentPage = Admin_1;
	}
	else
	{
		clcd_str("error");
		currentPage = OPEN;
	}
	
}

void changePw1() //관리자 모드에서 비번 바꾸기
{
	clcd_init_8bit();
	int i = 0;

	for(int i=0; i<4; i++)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(0,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			area1_PW[i] = key;
			i++;
			/*if(strcmp(buf,"*")==0)
			{
				clcd_str("Area1 PW changed!");
			}
			else if(strcmp(buf,"#")==0)
			{
				currentPage = OPEN;
			}*/
		}
		clcd_str("Area1 PW changed!");
	}
}

void userPwInput() // 유저 비번 확인
{
	clcd_init_8bit();
	clcd_str("Enter the PW");
	int i = 0;
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			inputPassword[i] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				checkUserPW(buf);
			}
			else if(strcmp(buf,"#")==0)
			{
				char buf[10]="";
				main();
			}
		}
	}
}

void checkUserPW(int buf) // 유저 모드 비번 확인
{
	clcd_init_8bit();
	int isMatch = 1;
	for (int j = 0; j<4; j++)
	{
		if(inputPassword[j] != area_PW[buf][j])
		{
			isMatch = 0;
		}
	}
	if(isMatch == 1)
	{
		clcd_str("Correct");
	}
	else
	{
		clcd_str("!error!");
	}
	//inputPassword[10]="";
	
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

