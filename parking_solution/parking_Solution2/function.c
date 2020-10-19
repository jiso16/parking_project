#include "parking.h"

//비밀번호, 키 관련 변수
char buf[10];
char input_password [4];
char inital_password [4];
char area_password [3][5];

int num2 ;

volatile int x;

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
	clcd_position(1,0);
	clcd_str("New PW:");
}
void AreaNum2()
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
		//i = 9;
		currentPage = Admin_PW_OK;
	}
	else
	{
		clcd_str("Wrong PW");
		currentPage = OPEN2;
	}
	
}
void UserPwInput() // 유저 비번 확인
{
	clcd_init_8bit();
	clcd_str("Enter the PW");
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