#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "clcd_D8.h"

char KeyScan();
void Init();
void AreaNum();
void PwInput();
void CheckAdminPW();
void print_Str();
void Open();
void Open2();
void io_setting();
void Warning();
void timer();
void ChangePw(int num);
void CheckUserPW(int num2);
void GateClose();
void GateOpen();
void InitUserMode();
void UserPwInput(int num);




enum eWindowPosition { OPEN, OPEN2, OPEN3,
	 KEY,KEY2, KEY_MODE,PW_INPUT,Admin_PW,Admin_PW_OK,
	AREA, Area_Num,Change_PW,Key_Change, PW_Change_OK,
	AREA2, Area_Num2, Gate_Open,Gate_Close,PW_Input} currentPage ;
	
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
	
volatile int x;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = -250;
	x++;
	
	switch(currentPage)
	{
		case OPEN :
		{
			if(x>1000)
			{
				//PORTA = ~PORTA;
				print_Str();
				
				currentPage = OPEN2;
				
				x = 0;
			}
			
			break;
		}
		case  OPEN2:
		{
			if(x>1000)
			{
				Open();
				
				currentPage = OPEN3;
				
				x = 0;
			}
			break;
		}
		case  OPEN3:
		{
			if(x>1000)
			{
				Open2();
				
				currentPage = KEY;
				
				x = 0;
			}
			break;
		}
		case  KEY_MODE:
		{
			if(x>1000)
			{
				Init();
				if(strcmp(buf,"1")==0)
				{
					//관리자모드 진입
					currentPage = PW_INPUT;
					
				}
				else if (strcmp (buf,"2")==0)
				{
					//유저모드 진입
					InitUserMode();
					currentPage = AREA2;
				}
				else
				{
					Warning();
				}
				
				x = 0;
			}
			break;
		}
		case PW_INPUT:
		{
			if(x>1000)
			{
				//PORTA = ~PORTA;
				PwInput();
				
				currentPage = KEY2;
				
				x = 0;
			}
			break;
		}
		case Admin_PW:
		{
			if(x>1000)
			{
				CheckAdminPW();
				
				x = 0;
			}
			break;
		}
		case Admin_PW_OK:
		{
			if(x>1000)
			{
				clcd_init_8bit();
				clcd_str("Which position");
				clcd_position(1,0);
				clcd_str("change the PW?");
							
				currentPage = AREA;
				x = 0;
			}
			break;
		}
		case Area_Num:
		{
			if(x>2000)
			{			
				AreaNum();
				
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
				else if(strcmp(buf,"#")==0)
				{
					clcd_init_8bit();
					currentPage = OPEN2;
				}
				else
				{
					Warning();
				}		
				
				x = 0;
			}
			break;
		}
		case PW_Change_OK:
		{
			clcd_init_8bit();
			clcd_str("Password changed!");
			currentPage = Admin_PW_OK;
		}
		case Area_Num2:
		{
			if(x>1500)
			{
				AreaNum();
				currentPage = PW_Input;
			}
		}
		case PW_Input:
		{
			if(x>2000)
			{				
				if (strcmp(buf,"1")==0)
				{
					UserPwInput(0);
				}
				else if(strcmp(buf,"2")==0)
				{
					UserPwInput(1);
				}
				else if(strcmp(buf,"3")==0)
				{
					UserPwInput(2);
				}
				else
				{
					Warning();
				}
				
				x = 0;
			}
			break;
		}
		case Gate_Open:
		{
			if(x>1500)
			{
				GateOpen();
				x = 0;
			}
			break;
		}
		case Gate_Close:
		{
			if(x>1500)
			{
				GateClose();
				x = 0;
			}
			break;
		}
	}
}


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

ISR(TIMER3_COMPA_vect)
{
	switch(cnt)
	{
		case 0:
		PORTD|=0x10;
		_delay_us(10);
		PORTD&=~0x10;
		EICRA=0x03; //인터럽트 0~3 설정
		EIFR=0xFF;  // 인터럽트 클리어 해주는 레지스터
		EIMSK=0x01; // 개별적 인터럽트 허용 레지스터
		break;
		
		case 1:
		PORTD|=0x20;
		_delay_us(10);
		PORTD&=~0x20;
		EICRA=0x0C;
		EIFR=0xFF;
		EIMSK=0x02;
		break;
		
		case 2:
		PORTD|=0x40;
		_delay_us(10);
		PORTD&=~0x40;
		EICRA=0x30;
		EIFR=0xFF;
		EIMSK=0x04;
		break;
	}
	if(++cnt>3)
	cnt=0;
}

void InitUserMode()
{
	clcd_init_8bit();
	clcd_str("Visitor mode.");
	clcd_position(1, 0);
	clcd_str("Enter Your Area");
}

void AreaNum()
{
	clcd_init_8bit();
	clcd_str("Area ");
	clcd_str(buf);
}

void PwInput() // 관리자모드 비번 입력
{
	clcd_init_8bit();

	clcd_str("Enter the Admin");
	clcd_position(1,0);
	clcd_str("password:");
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
 		currentPage = Admin_PW_OK;
	}
	else
	{
		clcd_str("Wrong PW");
		currentPage = OPEN2;
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
		clcd_init_8bit();
		clcd_str("Have a nice day");
				
		currentPage = Gate_Open;
	}
	else
	{
		clcd_str("Wrong PW");
		currentPage = OPEN2;
	}
	
}

void GateOpen()
{
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; TCCR1B=0x1A; OCR1A=3000; ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8ºÐ??
	
	OCR1A = 1900; // 0 degree
	
	currentPage = Gate_Close;
}

void GateClose()
{
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; TCCR1B=0x1A; OCR1A=3000; ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8ºÐ??

	OCR1A = 700; // 90 degree
	
	
	currentPage = OPEN2;
}



void Init()
{
	clcd_init_8bit();
	clcd_str("mode ");
	clcd_str(buf);
}

void Open()
{
	clcd_init_8bit();
	clcd_str("Select the mode");
	
}

void Open2()
{
	clcd_init_8bit();
	clcd_str("1) Admin mode");
	clcd_position(1, 0);
	clcd_str("2) Visitor mode");
}

void Warning()
{
	clcd_init_8bit();
	clcd_str("Wrong Number!");
	currentPage = OPEN;
}
void print_Str()
{
	
	clcd_position(0, 0);
	clcd_str("Parking System");
		
}

void io_setting()
{
	DDRA = 0xFF;
}

void timer()
{
	TCCR0 = ((1<<CS02)|(0<<CS01)|(0<<CS00));
	TCNT0 = -250;
	TIMSK = ((1<<TOIE0));
}

void ChangePw(int num) //관리자 모드에서 비번 바꾸기
{
	clcd_position(1,0);
	clcd_str("New PW:");
	int i = 7;
	while(1)
	{
		key=KeyScan();
		if(key != 0xFF)
		{
			clcd_position(1,i);
			sprintf(buf, "%c", key);
			clcd_str(buf);
			area_password[num][i-7] = key;
			i++;
			if(strcmp(buf,"*")==0)
			{
				currentPage = PW_Change_OK;
				break;
			}
		}
	}
}

int main()
{
	timer();
	io_setting();
	
	DDRD=0x70; // 트리거
	DDRF=0x07;
	TCCR3B=0x0C;
	OCR3A=3124;
	ETIMSK=0x10; //16000000/256/(1+ 3124)=20Hz=50ms
	
	sei();
	
	clcd_port_init();//CPU초기화
	clcd_init_8bit();//LCD초기화
	
	while (1)
	{
		switch(currentPage)
		{
			case KEY:
			{
				key=KeyScan();
				
				if(key != 0xFF)
				{
					sprintf(buf,"%c",key);
					currentPage = KEY_MODE;
				}
				break;
			}
			case KEY2:
			{
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
							currentPage = Admin_PW;
							//CheckAdminPW();
							break;
						}
					}
				}
				break;
			}
			case AREA:
			{
				key=KeyScan();
				
				if(key != 0xFF)
				{
					sprintf(buf,"%c",key);
					currentPage = Area_Num;
				}
				break;
			}
// 			case  Key_Change:
// 			{
// 				ChangePw();
// 			}
			case AREA2:
			{
				key=KeyScan();
				
				if(key != 0xFF)
				{
					sprintf(buf,"%c",key);
					currentPage = Area_Num2;
				}
				break;
			}
			
		}
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
	}
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
