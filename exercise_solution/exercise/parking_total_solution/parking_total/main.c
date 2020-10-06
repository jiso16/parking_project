#define F_CPU 16000000UL // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
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
void delay_us(unsigned int time_us);
void delay_ms(unsigned int time_ms);



enum eWindowPosition { OPEN, INIT, Admin_1, User_1} currentPage ;

//초음파센서 변수
volatile unsigned int  buf2[3],dist[3],start=0,end=0;
volatile unsigned char cnt=0,flag[3]={0,0,0};

//비밀번호, 키 관련 변수
char key;
char keybuf[30];
char buf[10];
char input_password [10];
char inital_password [10]="1234";
char area_password [3][5]= {" "," "," "};

ISR(INT0_vect) // 에코 PD0
{
	if(EICRA==0x03)
	start=TCNT3;
	else
	{
		end=TCNT3;
		buf2[0]=end-start;
		EIMSK=0;
		flag[0]=1;
		if (dist[0]<0.5)
		{
			PORTF &= ~0x01;
		}
		else
		{
			PORTF |= 0x01;
		}
	}
	EICRA^=0x01;
}
ISR(INT1_vect) // 에코 PD1
{
	if(EICRA==0x0C)
	start=TCNT3;
	else
	{
		end=TCNT3;
		buf2[1]=end-start;
		EIMSK=0;
		flag[1]=1;
		if (dist[1]<0.5)
		{
			PORTF &= ~0x02;
		}
		else
		{
			PORTF |= 0x02;
		}
	}
	EICRA^=0x04;
}
ISR(INT2_vect)  // 에코 PD2
{
	if(EICRA==0x30)
	start=TCNT3;
	else
	{
		end=TCNT3;
		buf2[2]=end-start;
		EIMSK=0;
		flag[2]=1;
		if (dist[2]<0.5)
		{
			PORTF &= ~0x04;
		}
		else
		{
			PORTF |= 0x04;
		}
	}
	EICRA^=0x10;
}

//트리거
ISR(TIMER3_COMPA_vect)
{
	switch(cnt)
	{
		case 0:
		PORTD|=0x10;
		delay_us(10);
		PORTD&=~0x10;
		EICRA=0x03; //인터럽트 0~3 설정
		EIFR=0xFF;  // 인터럽트 클리어 해주는 레지스터
		EIMSK=0x01; // 개별적 인터럽트 허용 레지스터
		break;
		
		case 1:
		PORTD|=0x20;
		delay_us(10);
		PORTD&=~0x20;
		EICRA=0x0C;
		EIFR=0xFF;
		EIMSK=0x02;
		break;
		
		case 2:
		PORTD|=0x40;
		delay_us(10);
		PORTD&=~0x40;
		EICRA=0x30;
		EIFR=0xFF;
		EIMSK=0x04;
		break;
	}
	if(++cnt>3)
		cnt=0;
}


int main()
{
	//초음파 센서 관련 포트설정 및 타이머 설정
	DDRD=0x70; // 트리거
	DDRF=0x07;
	TCCR3B=0x0C;
	OCR3A=3124;
	ETIMSK=0x10; //16000000/256/(1+ 3124)=20Hz=50ms
	sei();//SREG=0x80;
	
	//clcd 초기화 및 parking system 시작
	clcd_port_init();
	clcd_init_8bit();
	
	clcd_position(0, 0);
	clcd_str("Parking System");
	delay_ms(1500);
	clcd_init_8bit();
	
	while(1)
	{	
		if(flag[0])
		{
			flag[0]=0;
			dist[0]=(int)((float)buf2[0]/14.5);
		}
		if(flag[1])
		{
			flag[1]=0;
			dist[1]=(int)((float)buf2[1]/14.5);
		}
		if(flag[2])
		{
			flag[2]=0;
			dist[2]=(int)((float)buf2[2]/14.5);
		}
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

void delay_us(unsigned int time_us)
{
	register unsigned i;
	
	for(i = 0; i < time_us; i++)					/* 4 cycle +				*/
	{
		asm volatile(" PUSH  R0 ");				/* 2 cycle +				*/
		asm volatile(" POP   R0 ");				/* 2 cycle +				*/
		asm volatile(" PUSH  R0 ");				/* 2 cycle +				*/
		asm volatile(" POP   R0 ");				/* 2 cycle +				*/
		asm volatile(" PUSH  R0 ");				/* 2 cycle +				*/
		asm volatile(" POP   R0 ");				/* 2 cycle    =  16 cycle		*/
	}
}

void delay_ms(unsigned int time_ms)
{
	register unsigned int i;
	
	for(i = 0; i < time_ms ; i++) {
		delay_us(1000);
	}
}

void Open()
{
	clcd_init_8bit();
	clcd_str("Select the mode");
	delay_ms(2000);
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
	delay_ms(1000);
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
	delay_ms(3000);
	clcd_init_8bit();
}

void AdminAreaNum()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	delay_ms(1000);
	clcd_init_8bit();
}

void AreaNumber()
{
	clcd_init_8bit();
	clcd_str("Area ");
	sprintf(buf,"%c",key);
	clcd_str(buf);
	delay_ms(1000);
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
		delay_ms(1000);
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
				delay_ms(1000);
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
		delay_ms(1000);
		clcd_init_8bit();
		GateOpen();
		
		currentPage = OPEN;
	}
	else
	{
		clcd_str("Wrong PW");
		delay_ms(1000);
		currentPage = OPEN;
	}
	
}

void GateOpen()
{
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; TCCR1B=0x1A; OCR1A=3000; ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8ºÐÁÖ
	
	OCR1A = 1900; // 0 degree
	delay_ms(3000);
	OCR1A = 700; // 90 degree
	delay_ms(30);
	
	//currentPage = OPEN;
}





char KeyScan()
{

	char keybuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF

	PORTE=0xFF;         // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRE=0x0F;         // 비트0,1,2,3 출력으로 지정

	PORTE&=~1; // 1번째 줄 선택
	delay_ms(30);
	if((PINE&0x10)==0)keybuf='1';
	if((PINE&0x20)==0)keybuf='2';
	if((PINE&0x40)==0)keybuf='3';
	PORTE|=1; // 1번째 줄 해제

	PORTE&=~2; // 2번째 줄 선택
	delay_ms(30);
	if((PINE&0x10)==0)keybuf='4';
	if((PINE&0x20)==0)keybuf='5';
	if((PINE&0x40)==0)keybuf='6';
	PORTE|=2; // 2번째 줄 해제

	PORTE&=~4; // 3번째 줄 선택
	delay_ms(30);
	if((PINE&0x10)==0)keybuf='7';
	if((PINE&0x20)==0)keybuf='8';
	if((PINE&0x40)==0)keybuf='9';
	PORTE|=4; // 3번째 줄 해제

	PORTE&=~8; // 4번째 줄 선택
	delay_ms(30);
	if((PINE&0x10)==0)keybuf='*';
	if((PINE&0x20)==0)keybuf='0';
	if((PINE&0x40)==0)keybuf='#';
	PORTE|=8; // 4번째 줄 해제
	
	return keybuf;
}


