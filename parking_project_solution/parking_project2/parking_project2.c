#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void visitor_mode()
{
	int parkingPosition = 0;
	int password = 0;
	
	printf("Please enter a parking space:");
	scanf("%d", &parkingPosition);

	if (parkingPosition == 1)
	{
		printf("Enter the password:");
		scanf("%d", &password);
		if (password == 1234)
		{
			printf("Have a nice day!\n");
			
			//차단기 열리는 코드
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}

	}
	else if (parkingPosition == 2)
	{
		printf("Enter the password:");
		scanf("%d", &password);
		if (password == 1234)
		{
			printf("Have a nice day!\n");
			
			//차단기 열리는 코드
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}

	}
	else if (parkingPosition == 3)
	{
		printf("Enter the password:");
		scanf("%d", &password);
		if (password == 1234)
		{
			printf("Have a nice day!\n");
			
			//차단기 열리는 코드
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}

	}
	else if (parkingPosition == 4)
	{
		printf("Enter the password:");
		scanf("%d", &password);
		if (password == 1234)
		{
			printf("Have a nice day!\n");
			
			//차단기 열리는 코드
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}

	}
}

void Administor_mode()
{
	int Admin = 0;
	int adminPassowrd = 0;
	int password = 0;
	
	printf("This mode is Admin mode\n");
	printf("Are you adminisrot?\n\n");
	printf("1) Yes\n");
	printf("2) No\n");
	printf("Enter a number:");
	scanf("%d", &Admin);
	printf("\n");

	if (Admin == 1)
	{
		printf("Enter a Password:");
		scanf("%d", &adminPassowrd);
		if (adminPassowrd == 1234)
		{
			printf("What kind of work are you going to do?");
			printf("1)Change Password");
			scanf("%d", &password);
			if (password == 1)
			{
				//비밀번호 바꾸는 함수 부르기
			}
		}
		else
		{
			printf("Worng password!\n\n");
			Administor_mode();
		}
	}
	else
	{
		printf("Please use visitor mode\n\n");
		main();
		
	}
}

void automatic_in_breaker()
{
	//주차장 들어갈 때 차단기 열어주는 코드
	//서보모터 각도 제어, 열리는 시간
}

void automatic_out_breaker()
{
	//주차장에서 나올 때 차단기 열어주는 코드
	//서보모터 각도 제어, 열리는 시간, 센서사용?-자동차인식
}

void password_initialization()
{
	char push[] = "*";
	char initial[] = "";

	scanf("%s", &initial);
	
	if (strcmp(initial, push) == 0)
	{
		//비밀번호 초기화하는 코딩
	}
}

int main()
{
	int mode = 0;

	printf("This is parking system\n");
	printf("Please select the mode\n");
	printf("1) Visitor mode\n");
	printf("2) Admin mode\n");
	printf("mode: ");
	scanf("%d", &mode);
	printf("\n");

	if (mode == 1)// 일반인 모드
	{
		visitor_mode();
	}
	else
	{
		Administor_mode();
	}
}