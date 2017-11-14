#include <reg52.h>
sbit led = P1^0;
//sbit led2 = P1^1;
unsigned char count =0;
void init_clock_reg()  
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
}
void reset_clock() 
{
	TL0 = 0x00;		//设置定时初值
	TH0 = 0xDC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void init_clock_interrupt()
{
	ET0 = 1;
	EA = 1;
}
void time0_routine() interrupt 1
{
//	led2 = 0;
	
	count++;
	if(count == 100)	
	{
		count = 0;
		led = ~led;
	}
	reset_clock();
}

void main()
{
	init_clock_reg();
	init_clock_interrupt();
	reset_clock(); 
	led = 0;
	while(1);
}