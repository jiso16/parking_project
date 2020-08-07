
#define F_CPU 16000000L

#include <avr/io.h>

#include <util/delay.h>

​

#define PULSE_MIN 1000 //최소 펄스 지정

#define PULSE_MAX 5000 //최대 펄스 지정

​

void INIT_TIMER(void)

{

	TCCR1A |= (1<<WGM11);

	TCCR1B |= (1<<WGM12) | (1<<WGM13); //고속 PWM 모드, TOP : ICR1

	TCCR1B |= (1<<CS11); //분주율 8, 2MHz

	ICR1 = 40000; //20ms주기

	TCCR1A |= (1<<COM1A1); //비반전 모드

	DDRB |= (1<<PB1); //디지털 9번 핀

}

​

int main(void)

{

	INIT_TIMER();

	int i,j;

	while (1)

	{

		//서보 모터를 조금씩 움직이는 코드

		for(i=PULSE_MIN; i<=PULSE_MAX; i+=20)

		{

			OCR1A = i;

			_delay_ms(50);

		}

		for(j=PULSE_MAX; j>=PULSE_MIN; j-=20)

		{

			OCR1A = j;

			_delay_ms(50);

		}

	}

}