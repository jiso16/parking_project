#define F_CPU 8000000UL

#include <avr/io.h>//DDRX 선언때문에 사용, 표준라이브러리 함수
#include <util/delay.h>
#include <stdio.h>
#include "clcd_D8.h"//따움표는 사용자 정의함수


int main(void)
{
	clcd_port_init();
	
	// 관리자모드 변수선언
	/*int mode = 0;
	int Admin = 0;
	int adminPassowrd = 0;
	int number1 = 0;

	// 비밀번호 셋팅 변수선언
	int parking[4] = { 1234,1234,1234,1234 }; // 초기비밀번호
	int space = 0;
	int password = 0;
	//int i = 0;

	//일반인 모드 변수선언
	int parkingPosition = 0;
	int visitorPassword = 0;
*/
	while (1)
	{
		clcd_position(0, 0);
		clcd_str("Parking system");
		clcd_position(1, 0);
		clcd_str("Select the mode");
		_delay_ms(300);
		clcd_init_8bit();
		clcd_str("1) Admin mode");
		clcd_position(1, 0);
		clcd_str("2) Visitor mode");
		_delay_ms(300);
		clcd_init_8bit();
		clcd_str("Select the mode");
		clcd_position(1, 0);
		clcd_str("Press the number");
		_delay_ms(300);
		clcd_init_8bit();
		//scanf("%d", &mode);
		//clcd_str(" ");

		/*if (mode == 1)// 관리자 모드
		{
			clcd_str("Admin mode.");
			clcd_position(1, 0);
			clcd_str("R U admin?");
			_delay_ms(300);
			clcd_init_8bit();
			clcd_str("1) Yes");
			clcd_position(1, 0);
			clcd_str("2) No");
			_delay_ms(300);
			clcd_init_8bit();
			clcd_str("Press the number");
			//scanf("%d", &Admin);
			//clcd_str("");

			if (Admin == 1)
			{
				clcd_str("Enter a PW");
				//scanf("%d", &adminPassowrd);
				//clcd_str("");
				_delay_ms(300);
				clcd_init_8bit();
				if (adminPassowrd == 1234)
				{
					clcd_str("1)Change PW");
					clcd_position(1, 0);
					clcd_str("Enter number");
					_delay_ms(300);
					clcd_init_8bit();
					//scanf("%d", &number1);
					//clcd_str("");
					if (number1 == 1)
					{
						clcd_str("Which area?");
						_delay_ms(300);
						clcd_init_8bit();
						//scanf("%d", &space);

						if (space == 1)
						{
							clcd_str("Press PW of");
							clcd_position(1, 0);
							clcd_str("area 1");
							_delay_ms(300);
							clcd_init_8bit();
							//scanf("%d", &password);

							if (password == parking[0])
							{
								clcd_str("Enter PW you");
								clcd_position(1, 0);
								clcd_str("want to change");
								_delay_ms(300);
								clcd_init_8bit();
								//scanf("%d", &parking[0]);
								//clcd_str("Area1 PW is: %d", parking[0]); 입력받은 값 출력해야 됨
							}
							else
							{
								clcd_str("Wrong PW!");
								_delay_ms(300);
								clcd_init_8bit();
								main();
							}
						}
						else if (space == 2)
						{
							clcd_str("Press PW of");
							clcd_position(1, 0);
							clcd_str("area 1");
							_delay_ms(300);
							clcd_init_8bit();
							//scanf("%d", &password);

							if (password == parking[1])
							{
								clcd_str("Enter PW you");
								clcd_position(1, 0);
								clcd_str("want to change");
								_delay_ms(300);
								clcd_init_8bit();
								//scanf("%d", &parking[0]);
								//clcd_str("Area1 PW is: %d", parking[0]); 입력받은 값 출력해야 됨
							}
							else
							{
								clcd_str("Wrong PW!");
								_delay_ms(300);
								clcd_init_8bit();
								main();
							}
						}
						else if (space == 3)
						{
							clcd_str("Press PW of");
							clcd_position(1, 0);
							clcd_str("area 1");
							_delay_ms(300);
							clcd_init_8bit();
							//scanf("%d", &password);

							if (password == parking[2])
							{
								clcd_str("Enter PW you");
								clcd_position(1, 0);
								clcd_str("want to change");
								_delay_ms(300);
								clcd_init_8bit();
								//scanf("%d", &parking[0]);
								//clcd_str("Area1 PW is: %d", parking[0]); 입력받은 값 출력해야 됨
							}
							else
							{
								clcd_str("Wrong PW!");
								_delay_ms(300);
								clcd_init_8bit();
								main();
							}
						}
						else if (space == 4)
						{
							clcd_str("Press PW of");
							clcd_position(1, 0);
							clcd_str("area 1");
							_delay_ms(300);
							clcd_init_8bit();
							//scanf("%d", &password);

							if (password == parking[3])
							{
								clcd_str("Enter PW you");
								clcd_position(1, 0);
								clcd_str("want to change");
								_delay_ms(300);
								clcd_init_8bit();
								//scanf("%d", &parking[0]);
								//clcd_str("Area1 PW is: %d", parking[0]); 입력받은 값 출력해야 됨
							}
							else
							{
								clcd_str("Wrong PW!");
								_delay_ms(300);
								clcd_init_8bit();
								main();
							}
						}
					}
				}
				else
				{
					clcd_str("Wrong PW!");
					_delay_ms(300);
					clcd_init_8bit();

				}
			}
			else
			{
				clcd_str("Use Visitor Mode");
				_delay_ms(300);
				clcd_init_8bit();
				main();

			}



		}
		else if (mode == 2) // 일반인 모드
		{
			clcd_str("Enter UR Area");
			_delay_ms(300);
			clcd_init_8bit();
			//scanf("%d", &parkingPosition);

			if (parkingPosition == 1)
			{
				clcd_str("Enter the PW");
				_delay_ms(300);
				clcd_init_8bit();
				//scanf("%d", &visitorPassword);
				if (visitorPassword == parking[0])
				{
					clcd_str("Have a nice day!");
					_delay_ms(300);
					clcd_init_8bit();

					//차단기 열리는 코드
				}
				else
				{
					clcd_str("Wrong PW!");
					_delay_ms(300);
					clcd_init_8bit();
					main();
				}

			}
			else if (parkingPosition == 2)
			{
				clcd_str("Enter the PW");
				_delay_ms(300);
				clcd_init_8bit();
				//scanf("%d", &visitorPassword);
				if (visitorPassword == parking[1])
				{
					clcd_str("Have a nice day!");
					_delay_ms(300);
					clcd_init_8bit();

					//차단기 열리는 코드
				}
				else
				{
					clcd_str("Wrong PW!");
					_delay_ms(300);
					clcd_init_8bit();
					main();
				}

			}
			else if (parkingPosition == 3)
			{
				clcd_str("Enter the PW");
				_delay_ms(300);
				clcd_init_8bit();
				//scanf("%d", &visitorPassword);
				if (visitorPassword == parking[2])
				{
					clcd_str("Have a nice day!");
					_delay_ms(300);
					clcd_init_8bit();
					//차단기 열리는 코드
				}
				else
				{
					clcd_str("Wrong PW!");
					_delay_ms(300);
					clcd_init_8bit();
					main();
				}

			}
			else if (parkingPosition == 4)
			{
				clcd_str("Enter the PW");
				_delay_ms(300);
				clcd_init_8bit();
				//scanf("%d", &visitorPassword);
				if (visitorPassword == parking[3])
				{
					clcd_str("Have a nice day!");
					_delay_ms(300);
					clcd_init_8bit();

					//차단기 열리는 코드
				}
				else
				{
					clcd_str("Wrong PW!");
					_delay_ms(300);
					clcd_init_8bit();
					main();
				}

			}
		}
		else
		{
			clcd_str("Choose 1 or 2");
			_delay_ms(300);
			clcd_init_8bit();
			main();
		}*/
	}



}