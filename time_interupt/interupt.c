#include <reg52.h>
sbit led = P1^0;
//sbit led2 = P1^1;
unsigned char count =0;
void init_clock_reg()  
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
}
void reset_clock() 
{
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0xDC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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