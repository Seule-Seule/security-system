#include "Delay.h"

void Delay1us()		//@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void delay_us(unsigned short s)
{
	while(s--)
	{
		Delay1us();
	}
}

void delay_ms(unsigned short s)
{
	while(s--)
	{
		Delay1ms();
	}
}

void Delay40us()		//@11.0592MHz
{
	unsigned char i;

	i = 108;
	while (--i);
}

