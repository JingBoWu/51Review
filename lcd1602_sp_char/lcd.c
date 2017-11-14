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


Boolean lcd_busy()
{
	
	Boolean result;
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

//void lcd_pos(unsigned char pos)
//{
//	lcd_w_cmd(pos|0x80);
//}

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

//unsigned char  lcd_r_dat()
//{
//	unsigned char dat;
//	while(lcd_busy());
//	P2 = 0xff;//拉高电平，否则读取不了数据
//	RS = 1;
//	RW = 1;
//	EN = 0;
//	_nop_();
//	_nop_();
//	EN = 1;
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	dat = P2;
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	EN = 0;
//	
//	
//	return dat;	
//}

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

unsigned char  code table[]={
    0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,            //℃，代码 0x00
    0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,             //一，代码 0x01
    0x00,0x00,0x00,0x0e,0x00,0xff,0x00,0x00,            //二，代码 0x02
    0x00,0x00,0xff,0x00,0x0e,0x00,0xff,0x00,             //三，代码 0x03
    0x00,0x00,0xff,0xf5,0xfb,0xf1,0xff,0x00,               //四，代码 0x04
    0x00,0xfe,0x08,0xfe,0x0a,0x0a,0xff,0x00,            //五，代码 0x05
    0x00,0x04,0x00,0xff,0x00,0x0a,0x11,0x00,        //六，代码 0x06
    0x00,0x1f,0x11,0x1f,0x11,0x11,0x1f,0x00,        //日，代码 0x07
};



void main()
{
	
	unsigned char i;
	
	lcd_init();
	lcd_w_cmd(0x40);
for(i=0;i<8;i++)  
{
  lcd_w_dat(table[i]);
}  
lcd_w_cmd(0x80);
lcd_w_dat(0);



	while(1);

}

