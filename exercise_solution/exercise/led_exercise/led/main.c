#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB = 0b11111111;
	
	for(int i = 0; i<4; i++)
	{
		PORTB = 0b00100000;
		_delay_ms(500);
		PORTB = 0b00000000;
		_delay_ms(500);
	}
	return 0;
}