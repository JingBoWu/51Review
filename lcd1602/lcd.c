#include <reg52.h>
#include <intrins.h>

typedef bit Boolean			;


sbit RS = P0^7;
sbit RW = P0^6;
sbit EN = P0^5;

void delay (int m)
{
 unsigned char i,j;
 for (i=0;i<m;i++)
 for (j=0;j<253;j++);
}

void send_uart(unsigned char buf)
{

	SBUF = buf;
		while(!TI);
	TI = 0;
}

Boolean lcd_busy()
{
	
	Boolean result;

	send_uart(0xff);
	P2 = 0xff;
	RS = 0;
	RW = 1;
	EN = 0;
	_nop_();
	_nop_();
	EN = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	result = (Boolean)(P2&0x80);
	send_uart(P2);
	_nop_();
	EN = 0;

	return result;
}

void lcd_w_cmd(unsigned char cmd)
{
	while(lcd_busy());
	RS = 0;
	RW = 0;
	EN = 0;
	_nop_();
	_nop_();
	P2 = cmd;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EN = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EN = 0;
	_nop_();	
}

void lcd_pos(unsigned char pos)
{
	lcd_w_cmd(pos|0x80);
}

void lcd_w_dat(unsigned char dat)
{
	 while(lcd_busy());
	RS = 1;
	RW = 0;
	EN = 0;
	_nop_();
	_nop_();
	P2 = dat;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EN = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EN = 0;
	_nop_();
}

unsigned char  lcd_r_dat()
{
	unsigned char dat;
	while(lcd_busy());
	P2 = 0xff;//拉高电平，否则读取不了数据
	RS = 1;
	RW = 1;
	EN = 0;
	_nop_();
	_nop_();
	EN = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	dat = P2;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EN = 0;
	
	
	return dat;	
}

void lcd_init()
{
//	delay(1);
//	lcd_w_cmd(0x38);
//	delay(5);
//	lcd_w_cmd(0x38);
//	delay(5);
//	lcd_w_cmd(0x38);
	delay(5);
	lcd_w_cmd(0x38);
	delay(1);
	lcd_w_cmd(0x08);
	delay(1);
	lcd_w_cmd(0x01);
	delay(1);
	lcd_w_cmd(0x06);
	delay(1);
	lcd_w_cmd(0x0c);
	
}

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

	TI = 0;
}
unsigned char flag = 1;
void main()
{
	
	unsigned char a;
	
	init_uart();

	while(flag);

	lcd_init();
	lcd_pos(0x0);
	lcd_w_dat('c');
	//lcd_pos(0x1);
	lcd_w_dat('d');
	//lcd_pos(0x2);
	lcd_w_dat('e');

	lcd_pos(0x1);
	a = lcd_r_dat();
	lcd_pos(0x4);
	lcd_w_dat(a);
	//P1 = a;
	while(1);

}

void uart_routine() interrupt 4
{
	//led =~led;
	unsigned char num;
	if(RI)
	{
		num = SBUF;
		RI = 0;
		
		if(num == 0x01)
		{
			flag = 0;
			send_uart(0xff);
		}
	}
}

