#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int mode = 0;
	int parkingPosition = 0;
	int password = 0;
	int Admin = 0;
	int adminPassowrd = 0;

	printf("This is parking system\n");
	printf("Please select the mode\n");
	printf("1) Visitor mode\n");
	printf("2) Admin mode\n");
	printf("mode: ");
	scanf("%d", &mode);
	printf("\n");

	while (1)
	{
		if (mode == 1)//�湮�� ���
		{
			printf("Please enter a parking space:");
			scanf("%d", &parkingPosition);

			if (parkingPosition == 1)
			{
				printf("Enter the password:");
				scanf("%d", &password);
				if (password == 1234)
				{
					printf("Have a nice day!\n");
					break;
					//���ܱ� ������ �ڵ�
				}
				else
				{
					printf("Worng password!\n\n");
					//printf("\n");
				}

			}
			else if (parkingPosition == 2)
			{
				printf("Enter the password:");
				scanf("%d", &password);
				if (password == 1234)
				{
					printf("Have a nice day!\n");
					break;
					//���ܱ� ������ �ڵ�
				}
				else
				{
					printf("Worng password!\n\n");
				}

			}
			else if (parkingPosition == 3)
			{
				printf("Enter the password:");
				scanf("%d", &password);
				if (password == 1234)
				{
					printf("Have a nice day!\n");
					break;
					//���ܱ� ������ �ڵ�
				}
				else
				{
					printf("Worng password!\n\n");
				}

			}
			else if (parkingPosition == 4)
			{
				printf("Enter the password:");
				scanf("%d", &password);
				if (password == 1234)
				{
					printf("Have a nice day!\n");
					break;
					//���ܱ� ������ �ڵ�
				}
				else
				{
					printf("Worng password!\n\n");
				}

			}
			
		}
		else if (mode == 2)
		{
			printf("This mode is Admin mode\n");
			printf("Are you adminisrot?\n");
			printf("1) Yes\n");
			printf("2) No\n");
			printf("Enter a number:");
			scanf("%d", &Admin);

			if (Admin == 1)
			{
				printf("Enter a Password:");
				scanf("%d", &adminPassowrd);
				if (adminPassowrd == 1234)
				{
					printf("What kind of work are you going to do?");
					break; // ���߿� ������ ��, �ڵ� ���ư����� Ȯ�ο�
					//��й�ȣ �ٲٴ� �ڵ�
				}
				else 
				{
					printf("Worng password!\n\n");
				}
			}
			else
			{
				printf("Please use visitor mode\n\n");
				//�ٽ� ù��° ���Ϲ����� ���� �ڵ�
			}
		}
	}
}