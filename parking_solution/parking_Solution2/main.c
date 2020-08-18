#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "clcd_D8.h"

char KeyScan();
void PwInput(); //관리자 모드 비밀번호 입력
void CheckAdminPW(); // 관리자 모드 비밀번호 확인
void ChangePw();//관리자 모드에서 비번 바꾸기
void UserPwInput (); // 유저 비밀번호 입력
void CheckUserPW(); // 유저 비밀번호 확인
void Open();
void Init();
void InitUserMode();
void Warning();
void AdminAreaNum();
void AreaNumber();

enum eWindowPosition { OPEN, INIT, Admin_1, User_1} currentPage ;

char key;
char keybuf[30];
char buf[10];
char input_password [10];
char inital_password [10]="1234";
char area_password [4][10]= {"1234","1234","1234","1234"};

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
					Open();
					break;
				}
				
				case INIT:
				{
					Init();
					
					if(strcmp(buf,"1")==0)
					{
						//관리자모드 진입
						PwInput();
						
					}
					else if (strcmp (buf,"2")==0)
					{
						//유저모드 진입
						InitUserMode();
					}
					else
					{
						Warning();
					}
					break;
				}
				case Admin_1 :
				{				
					AdminAreaNum();	
					
					if (strcmp(buf,"1")==0)
					{
						ChangePw(0);
					}
					else if(strcmp(buf,"2")==0)
					{
						ChangePw(1);
					}
					else if(strcmp(buf,"3")==0)
					{
						ChangePw(2);
					}
					else if(strcmp(buf,"4")==0)
					{
						ChangePw(3);
					}
					else
					{
						Warning();
					}
					break;
				}
				case User_1 :
				{
					AreaNumber();				
					if(strcmp(buf,"1")==0)
					{
						UserPwInput(0);
					}
					else if (strcmp(buf,"2")==0)
					{
						UserPwInput(1);
					}
					else if (strcmp(buf,"3")==0)
					{
						UserPwInput(2);
					}
					else if (strcmp(buf,"4")==0)
					{
						UserPwInput(3);
					}
					else
					{
						Warning();

					}
					
					break;
					
				}
			}
		}
	}
}
void Open()
{
	clcd_init_8bit();
	clcd_str("Select the mode");
	_delay_ms(200);
	clcd_init_8bit();
	clcd_str("1) Admin mode");
	clcd_position(1, 0);
	clcd_str("2) Visitor mode");
	currentPage = INIT;
}

void Init()
{
	clcd_init_8bit();
	clcd_str("mode ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	_delay_ms(100);
	clcd_init_8bit();
}

void InitUserMode()
{
	currentPage = User_1;
	clcd_str("Visitor mode.");
	clcd_position(1, 0);
	clcd_str("Enter Your Area");
}

void Warning()
{
	currentPage = OPEN;
	clcd_str("Wrong Number!");
	_delay_ms(300);
	clcd_init_8bit();
}

void AdminAreaNum()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	_delay_ms(100);
	clcd_init_8bit();
}

void AreaNumber()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	_delay_ms(100);
	clcd_init_8bit();
}

void PwInput() // 관리자모드 비번 입력
{
	clcd_init_8bit();

	clcd_str("Enter the Admin");
	clcd_position(1,0);
	clcd_str("password:");
	int i = 9;
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			input_password[i-9] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				CheckAdminPW();
				break;
			}
		}
	}
}

void CheckAdminPW() // 관리자 모드 비번 확인
{
	clcd_init_8bit();
	int isMatch = 1;
	for (int j = 0; j<4; j++)
	{
		if(input_password[j] != inital_password[j])
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

void ChangePw(int num) //관리자 모드에서 비번 바꾸기
{
	clcd_init_8bit();
	int i = 0;
	clcd_str("Enter the new PW");
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			area_password[num][i] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				clcd_init_8bit();
				clcd_str("Password changed!");
				_delay_ms(100);
				currentPage = OPEN;
				break;
			}
		}
	}
	clcd_str("Area1 PW changed!");
}

void UserPwInput(int num) // 유저 비번 확인
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
			input_password[i] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				CheckUserPW(num);
				break;
			}
		}
	}
}

void CheckUserPW(int num2) // 유저 모드 비번 확인
{
	clcd_init_8bit();
	int isMatch = 1;
	for (int j = 0; j<4; j++)
	{
		if(input_password[j] != area_password[num2][j])
		{
			isMatch = 0;
		}
	}
	if(isMatch == 1)
	{
		clcd_str("Correct");
		_delay_ms(100);
		currentPage = OPEN;
		//게이트 열리는 코딩
	}
	else
	{
		clcd_str("!error!");
		_delay_ms(100);
		currentPage = OPEN;
	}
	
}

char KeyScan()
{

	char keybuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)keybuf='1';
	if((PINE&0x20)==0)keybuf='2';
	if((PINE&0x40)==0)keybuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)keybuf='4';
	if((PINE&0x20)==0)keybuf='5';
	if((PINE&0x40)==0)keybuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)keybuf='7';
	if((PINE&0x20)==0)keybuf='8';
	if((PINE&0x40)==0)keybuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	_delay_ms(2);
	if((PINE&0x10)==0)keybuf='*';
	if((PINE&0x20)==0)keybuf='0';
	if((PINE&0x40)==0)keybuf='#';
	PORTE|=8; // 4번째 줄 해제
	
	return keybuf;
}

