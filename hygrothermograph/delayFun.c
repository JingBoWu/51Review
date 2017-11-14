#include "common.h"

void delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void delay1ms()
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void delay(unsigned char ms)
{
	do
	{
		delay1ms();
	}while(--ms);
}