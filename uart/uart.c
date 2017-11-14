#include <reg52.h>
unsigned char num;
sbit led = P1^0;
void init_uart()
{
	// setup uart
	PCON |=0x80;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	//set T1 as 8 bit mode
	TMOD &=0x0F;
	TMOD |=0x20;
	TH1 = 0xfc ;
	TL1 = 0xfc;
	TF1 = 0;
	TR1 = 1;
	//enable interrupt
	ES = 1;
	EA = 1;
}

void main()
{
	init_uart();
   	led = 0;
	while(1);
}

void uart_routine() interrupt 4
{
	led =~led;
	if(RI)
	{
		num = SBUF;
		RI = 0;
		
		num++;
		SBUF = num;
		while(!TI);
		TI = 0;
	}
}