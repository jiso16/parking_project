#include "parking.h"
#include "clcd_D8.h"

//비밀번호, 키 관련 변수
char key;
char buf[10];
char input_password [4];
char inital_password [4]="1234";
char area_password [3][5]= {" "," "," "};
int i = 9;
int k = 7;
int m = 0;
int num = 0;
int num2 = 0;

volatile int x;

volatile unsigned int  buf2[3],dist[3],start=0,end=0;
volatile unsigned char cnt=0,flag[3]={0,0,0};

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
					num = 0;
					currentPage = KEY3;

				}
				else if(strcmp(buf,"2")==0)
				{
					num = 1;
					currentPage = KEY3;
				}
				else if(strcmp(buf,"3")==0)
				{
					num = 2;
					currentPage = KEY3;
				}
				else if(strcmp(buf,"#")==0)
				{
					clcd_init_8bit();
					currentPage = OPEN2;
				}

 				break;
				
						
				x = 0;
			}
			break;
		}
		case PW_Change_OK:
		{
			if(x>1500)
			{
				clcd_init_8bit();
				clcd_str("Password changed!");
				
				currentPage = Admin_PW_OK;
				x = 0;
			}	
			break;
		}
		case Area_Num2:
		{
			if(x>1500)
			{
				AreaNum2();
				currentPage = PW_Input;
				x=0;
			}
			break;
		}
		case PW_Input:
		{
			if(x>1500)
			{
				UserPwInput();
				if (strcmp(buf,"1")==0)
				{
					num2 = 0;
					currentPage = KEY4;

				}
				else if(strcmp(buf,"2")==0)
				{
					num2 = 1;
					currentPage = KEY4;
				}
				else if(strcmp(buf,"3")==0)
				{
					num2 = 2;
					currentPage = KEY4;
				}
				else
				{
					Warning();
				}
				x=0;
			}
			
			break;
		}
		case Check_User_PW:
		{
			if(x>1500)
			{
				CheckUserPW(num2);
								
				x = 0;
				
			}
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
	
	int i = 9;
	
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
				
				key=KeyScan();
				
				if(key != 0xFF)
				{
					clcd_position(1,i);
					sprintf(buf,"%c",key);
					clcd_str(buf);
					input_password[i-9] = key;
					i++;
					if(strcmp(buf,"*")==0)
					{
						i = 9;
						currentPage = Admin_PW;
						
						break;
					}			
				}
				break;
			}
			break;
			case KEY3:
			{
				key=KeyScan();
				if(key != 0xFF)
				{
					clcd_position(1,k);
					sprintf(buf, "%c", key);
					clcd_str(buf);
					area_password[num][k-7] = key;
					k++;
					if(strcmp(buf,"*")==0)
					{
						k = 7;
						currentPage = PW_Change_OK;
						break;
						
					}
				}
				break;
			}
			break;
			case KEY4:
			{
				key=KeyScan();
				if(key != 0xFF)
				{
					clcd_position(1,m);
					sprintf(buf, "%c", key);
					clcd_str(buf);
					input_password[m] = key;
					m++;
					if(strcmp(buf,"*")==0)
					{
						m = 0;
						currentPage = Check_User_PW;
					}
				}
				break;
			}
			break;
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

