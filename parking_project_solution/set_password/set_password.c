#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	// 관리자모드 변수선언
	int mode = 0;
	int Admin = 0;
	int adminPassowrd = 0;
	int number1 = 0;

	// 비밀번호 셋팅 변수선언
	int parking[4] = { 1234,1234,1234,1234 }; // 초기비밀번호
	int space = 0;
	int password = 0;
	int i = 0;

	//일반인 모드 변수선언
	int parkingPosition = 0;
	int visitorPassword = 0;

	while (1)
	{
		printf("This is parking system.\n");
		printf("Please select the mode.\n");
		printf("1) Admin mode\n");
		printf("2) Visitor mode\n");
		printf("Please enter the mode number: ");
		scanf("%d", &mode);
		printf("\n");

		if (mode == 1)// 관리자 모드
		{
			printf("This mode is Admin mode.\n");
			printf("Are you adminisrot?\n\n");
			printf("1) Yes\n");
			printf("2) No\n");
			printf("Please enter the number:");
			scanf("%d", &Admin);
			printf("\n");

			if (Admin == 1)
			{
				printf("Enter a Password:");
				scanf("%d", &adminPassowrd);
				printf("\n");
				if (adminPassowrd == 1234)
				{
					printf("What kind of work are you going to do?\n");
					printf("1)Change Password\n");
					printf("Enter the number: ");
					scanf("%d", &number1);
					printf("\n");
					if (number1 == 1)
					{
						printf("Which digit of the password will you change?: ");
						scanf("%d", &space);

						if (space == 1)
						{
							printf("Enter the password for location 1: ");
							scanf("%d", &password);

							if (password == parking[0])
							{
								printf("Enter the password you want to change: ");
								scanf("%d", &parking[0]);
								printf("\nparking1 password is: %d\n\n", parking[0]);
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

							if (password == parking[1])
							{
								printf("Enter the password you want to change:");
								scanf("%d", &parking[1]);
								printf("\nparking2 password is: %d\n\n", parking[1]);
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

							if (password == parking[2])
							{
								printf("Enter the password you want to change:");
								scanf("%d", &parking[2]);
								printf("\nparking3 password is: %d\n\n", parking[2]);
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

							if (password == parking[3])
							{
								printf("Enter the password you want to change:");
								scanf("%d", &parking[3]);
								printf("\nparking4 password is: %d\n\n", parking[3]);
							}
							else
							{
								printf("Worng password!\n\n");
								main();
							}
						}
					}
				}
				else
				{
					printf("Worng password!\n\n");

				}
			}
			else
			{
				printf("Please use visitor mode\n\n");
				main();

			}



		}
		else if(mode==2) // 일반인 모드
		{
			printf("Please enter the number of your seat: ");
			scanf("%d", &parkingPosition);

			if (parkingPosition == 1)
			{
				printf("Enter the password:");
				scanf("%d", &visitorPassword);
				if (visitorPassword == parking[0])
				{
					printf("\nHave a nice day!\n\n");

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
				scanf("%d", &visitorPassword);
				if (visitorPassword == parking[1])
				{
					printf("\nHave a nice day!\n\n");

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
				scanf("%d", &visitorPassword);
				if (visitorPassword == parking[2])
				{
					printf("\nHave a nice day!\n\n");

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
				scanf("%d", &visitorPassword);
				if (visitorPassword == parking[3])
				{
					printf("\nHave a nice day!\n\n");

					//차단기 열리는 코드
				}
				else
				{
					printf("Worng password!\n\n");
					main();
				}

			}
		}
		else
		{
			printf("Choose between 1 and 2.\n");
			main();
		}
	}
}