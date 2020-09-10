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
void GateOpen();
void getEcho(int ch);
int UltrasonicSensor(void);

enum eWindowPosition { OPEN, INIT, Admin_1, User_1} currentPage ;

//초음파센서 설정
#define Trig1_ON PORTD|=1 //트리거1
#define Trig2_ON PORTD|=2 //트리거2
#define Trig3_ON PORTD|=4 //트리거3

#define Trig1_OFF PORTD&=~1 //트리거1
#define Trig2_OFF PORTD&=~2 //트리거2
#define Trig3_OFF PORTD&=~4 //트리거3

//
char key;
char keybuf[30];
char buf[10];
char input_password [10];
char inital_password [10]="1234";
char area_password [3][5]= {" "," "," "};

//초음파센서 변수

char s[30];
unsigned int range_I, range[4];
float range_F;

char temp[3]={'0','0','0'};




int main()
{
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_position(0, 0);
	clcd_str("Parking System");
	_delay_ms(2000);
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

void getEcho(int ch){ // ch=0~3
	while(!(PIND&(0x10<<ch)));  // Wait for echo pin to go high
	TCNT1=0x00; TCCR1B=0x02;    // 1:8 prescaler = 0.5us
	while(PIND&(0x10<<ch));     // Wait for echo pin to go low
	TCCR1B=0x08; range_I=TCNT1; // the range in CM
	range_F=(float)range_I;
	range_F/=11.6; // mm
	range[ch]=(unsigned int)range_F; // range[ch]에 저장
}

// int UltrasonicSensor(void)
// {
//
// 	DDRD=0x0F;  // PD0~3 ouput Trigger, PD4~7 input Echo
// 	DDRF=0x07;  //led output
//
// 	TCCR1B=0x08;  // Set timer up in CTC mode
// 	_delay_ms(100);
//
// 	while(1)
// 	{
// 		_delay_ms(25); Trig1_ON; _delay_us(10); Trig1_OFF; getEcho(0);
//
// 		if ((range[0]<50)) // range[0]이 범위 안일 때
// 		{
// 			_delay_ms(25); Trig2_ON; _delay_us(10); Trig2_OFF; getEcho(1);
//
//
// 			if ((range[0]<50) && (range[1]<50))
// 			{
// 				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
//
// 				if ((range[0]<50) && (range[1]<50) && (range[2]<50))
// 				{
// 					PORTF = 0b00000000;
// 				}
// 				else if((range[0]<50) && (range[1]<50) && (range[2]>50))
// 				{
// 					PORTF = 0b00000100;
// 				}
// 			}
// 			else if((range[0]<50) && (range[1]>50))
// 			{
// 				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
//
// 				if ((range[0]<50) && (range[1]>50) && (range[2]<50))
// 				{
// 					PORTF = 0b00000010;
// 				}
// 				else if((range[0]<50) && (range[1]>50) && (range[2]>50))
// 				{
// 					PORTF = 0b00000110;
// 				}
//
// 			}
// 		}
// 		else if(range[0]>50) // range[0]이 범위 밖일 때
// 		{
// 			_delay_ms(25); Trig2_ON; _delay_us(10); Trig2_OFF; getEcho(1);
// 			if((range[0]>50) && (range[1]<50))
// 			{
// 				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
// 				if ((range[0]>50) && (range[1]<50) && (range[2]<50))
// 				{
// 					PORTF = 0b00000001;
// 				}
// 				else if ((range[0]>50) && (range[1]<50) && (range[2]>50))
// 				{
// 					PORTF = 0b00000101;
// 				}
// 			}
// 			else if((range[0]>50) && (range[1]>50))
// 			{
// 				_delay_ms(25); Trig3_ON; _delay_us(10); Trig3_OFF; getEcho(2);
// 				if ((range[0]>50) && (range[1]>50) && (range[2]<50))
// 				{
// 					PORTF = 0b00000011;
// 				}
// 				else if ((range[0]>50) && (range[1]>50) && (range[2]>50))
// 				{
// 					PORTF = 0b00000111;
// 				}
// 			}
//
// 		}
//
// 	}
// }

void Open()
{
	clcd_init_8bit();
	clcd_str("Select the mode");
	_delay_ms(2000);
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
	_delay_ms(1000);
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
	_delay_ms(3000);
	clcd_init_8bit();
}

void AdminAreaNum()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	_delay_ms(1000);
	clcd_init_8bit();
}

void AreaNumber()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	_delay_ms(1000);
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
		_delay_ms(1000);
		clcd_init_8bit();
		clcd_str("Which position");
		clcd_position(1,0);
		clcd_str("change the PW?");
		currentPage = Admin_1;
	}
	else
	{
		clcd_str("Wrong PW");
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
				_delay_ms(1000);
				currentPage = OPEN;
				break;
			}
		}
	}
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
		_delay_ms(1000);
		clcd_init_8bit();
		GateOpen();
		currentPage = OPEN;
		//게이트 열리는 코딩
	}
	else
	{
		clcd_str("Wrong PW");
		_delay_ms(1000);
		currentPage = OPEN;
	}
	
}

void GateOpen()
{
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; TCCR1B=0x1A; OCR1A=3000; ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8ºÐÁÖ
	
	OCR1A = 1900; // 0 degree
	_delay_ms(3000);
	OCR1A = 700; // 90 degree
	_delay_ms(30);
	
	//currentPage = OPEN;
}


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


