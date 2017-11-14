#define MAX_COUNT 250
#define MID_COUNT 150
unsigned char clock_count =0;
sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;

void init_clock_reg()  
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	led0 = 1;
	led1 = 1;
	led2 = 1;

}
void reset_clock()//10ms 
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

	led0 = 0;
}

void time0_routine() interrupt 1
{
//	led2 = 0;
	
	clock_count++;
	if(clock_count == MID_COUNT)	
	{
		led1 = 0;
	}
	if(clock_count == MAX_COUNT)	
	{
		led2 = 0;
		ask_for_data();
		
		clock_count = 0;
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);
		delay(100);

		led1 = 1;
		led2 = 1;

	}

	reset_clock();
}