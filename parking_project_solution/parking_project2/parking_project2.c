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
			
			//���ܱ� ������ �ڵ�
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
			
			//���ܱ� ������ �ڵ�
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
			
			//���ܱ� ������ �ڵ�
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
			
			//���ܱ� ������ �ڵ�
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
				//��й�ȣ �ٲٴ� �Լ� �θ���
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
	//������ �� �� ���ܱ� �����ִ� �ڵ�
	//�������� ���� ����, ������ �ð�
}

void automatic_out_breaker()
{
	//�����忡�� ���� �� ���ܱ� �����ִ� �ڵ�
	//�������� ���� ����, ������ �ð�, �������?-�ڵ����ν�
}

void password_initialization()
{
	char push[] = "*";
	char initial[] = "";

	scanf("%s", &initial);
	
	if (strcmp(initial, push) == 0)
	{
		//��й�ȣ �ʱ�ȭ�ϴ� �ڵ�
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

	if (mode == 1)// �Ϲ��� ���
	{
		visitor_mode();
	}
	else
	{
		Administor_mode();
	}
}