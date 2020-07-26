#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void visitor_mode() // 일반 방문자 모드
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



void set_password() // 비밀번호 바꾸는 코딩
{
	int parking[4] = { 1234,1234,1234,1234 }; // 초기비밀번호

	int space = 0;
	int password = 0;
	int i = 0;

	printf("Which digit of the password will you change?: ");
	scanf("%d", &space);

	if (space == 1)
	{
		printf("Enter the password for location 1: ");
		scanf("%d", &password);

		if (password == 1234)
		{
			printf("Enter the password you want to change: ");
			scanf("%d", &parking[0]);
			printf("\nparking1 password is: %d", parking[0]);
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}
	}
	else if (space == 2)
	{
		printf("Enter the password for location 2: ");
		scanf("%d", &password);

		if (password == 1234)
		{
			printf("Enter the password you want to change:");
			scanf("%d", &parking[1]);
			printf("\nparking1 password is: %d", parking[1]);
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}
	}
	else if (space == 3)
	{
		printf("Enter the password for location 3: ");
		scanf("%d", &password);

		if (password == 1234)
		{
			printf("Enter the password you want to change:");
			scanf("%d", &parking[2]);
			printf("\nparking1 password is: %d", parking[2]);
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}
	}
	else if (space == 4)
	{
		printf("Enter the password for location 4: ");
		scanf("%d", &password);

		if (password == 1234)
		{
			printf("Enter the password you want to change:");
			scanf("%d", &parking[3]);
			printf("\nparking1 password is: %d", parking[3]);
		}
		else
		{
			printf("Worng password!\n\n");
			main();
		}
	}
}
void Administor_mode() // 관리자모드
{
	int Admin = 0;
	int adminPassowrd = 0;
	int number1 = 0;

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
			printf("What kind of work are you going to do?\n");
			printf("1)Change Password\n");
			printf("Enter the number: ");
			scanf("%d", &number1);
			if (number1 == 1)
			{
				set_password();
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