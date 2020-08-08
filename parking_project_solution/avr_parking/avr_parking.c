#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

enum WindowPosition { INIT, Admin_1, Admin_2, User_1, User_PW1,
	User_PW2, User_PW3, User_PW4, 
	Admin_Pw1 ,Admin_Pw2, Admin_Pw3, Admin_Pw4 } currentPage;


int main()
{
	char buf[10];
	char key1 = "1234";
	char key2 = "1234";
	char key3 = "1234";
	char key4 = "1234";

	printf("parking System\n");
	printf("Select mode\n\n");
	printf("1)Admin mode\n");
	printf("2)visitor mode\n\n");


	while (1)
	{
		scanf("%s", &buf);

		//printf("%s", buf);
		
		if (strcmp(buf , "0")==0)
		{
			continue;
		}
		else
		{
			switch(currentPage)
			{
				case INIT :
				{
					if (strcmp(buf, "1") == 0)
					{
						//관리자모드 진입
						printf("Amin mode");
						printf("Enter the PW");
						currentPage = Admin_1;
						break;

					}
					else if (strcmp(buf, "2") == 0)
					{
						//유저모드 진입
						puts("visitor mode");
						puts("Enter the your area:");
						currentPage = User_1;
						break;
					}
					else
					{
						
						puts("Wrong Mode");
						main();
					}

				}
				case Admin_1:
				{

					if (strcmp(buf,"1234") == 0)
					{
						currentPage = Admin_2;
						puts("PW is correct");
						puts("Which space will you change the password for?");
						break;
					}
					else
					{
						puts("Wrong PW");
						main();				
					}					
				}
				case User_1:
				{
					if (strcmp(buf, "1") == 0)
					{
						currentPage = User_PW1;
						puts("Area 1");
						puts("Enter the PW");
						break;
					}
					else if (strcmp(buf, "2") == 0)
					{
						currentPage = User_PW2;
						puts("Area 2");
						puts("Enter the PW");
						break;
					}
					else if (strcmp(buf, "3") == 0)
					{
						currentPage = User_PW3;
						puts("Area 3");
						puts("Enter the PW");
						break;
					}
					else if (strcmp(buf, "4") == 0)
					{
						currentPage = User_PW4;
						puts("Area 4");
						puts("Enter the PW");
						break;
					}
					else
					{
						puts("Wrong PW");
						main();
					}
				}
				case Admin_2:
				{
					if (strcmp(buf, "1") == 0)
					{
						puts("enter the number you want to change.");
						currentPage = Admin_Pw1;
						break;
					}
					else if (strcmp(buf, "2") == 0)
					{
						puts("enter the number you want to change.");
						currentPage = Admin_Pw2;
						break;
					}
					else if (strcmp(buf, "3") == 0)
					{
						puts("enter the number you want to change.");
						currentPage = Admin_Pw3;
						break;
					}
					else if (strcmp(buf, "4") == 0)
					{
						puts("enter the number you want to change.");
						currentPage = Admin_Pw4;
						break;
					}
					else
					{
						puts("Wrong number");
						main();
					}
				}
				case User_PW1:
				{
					if(strcmp(buf, key1)==0);
					{
						puts("Area 1");
						puts("Have a nice Day!");
						main();
					}
					/*{
						puts("Wrong PW");
						main();
					}*/
				
				}
				case User_PW2:
				{
					if (strcmp(buf, key2) == 0);
					{
						puts("Area 2");
						puts("Have a nice Day!");
						main();
					}
					/*{
						puts("Wrong PW");
						main();
					}*/

				}
				case User_PW3:
				{

					if (strcmp(buf, key3) == 0);
					{
						puts("Area 3");
						puts("Have a nice Day!");
						main();
					}
					/*{
						puts("Wrong PW");
						main();
					}*/

				}
				case User_PW4:
				{
					if (strcmp(buf, key4) == 0);
					{
						puts("Area 4");
						puts("Have a nice Day!");
						main();
					}
					/*{
						puts("Wrong PW");
						main();
					}*/

				}
				case Admin_Pw1:
					key1 = buf;
					main();

				case Admin_Pw2:
					key2 = buf;
					main();

				case Admin_Pw3:
					key3= buf;
					main();

				case Admin_Pw4:
					key4 = buf;
					main();

			}
		}
	}
}