#include "lcd.h"

unsigned char  code table[]={
    0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,            //¡æ£¬´úÂë 0x00
};

unsigned char code tem_start_str[]=" Tem: ";
unsigned char code rh_start_str[]="  RH: ";

void lcd_w_cmd(unsigned char cmd);
void lcd_pos(unsigned char pos);
void lcd_w_dat(unsigned char dat);
void lcd_init_cgram();


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

void lcd_init()
{
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
	delay(1);
	lcd_init_cgram();	
}

void lcd_init_cgram()
{
	lcd_w_cmd(0x40);
	for(i=0;i<8;i++)  
	{
  		lcd_w_dat(table[i]);
	}  	
}
void lcd_TH_init()
{
	lcd_pos(0);
	i=0;
	while(tem_start_str[i] != '\0')
	{
		lcd_w_dat(tem_start_str[i]);
		i++;
	}
	lcd_w_dat('+');
	lcd_w_dat('0');
	lcd_w_dat('0');
	lcd_w_dat('.');
	lcd_w_dat('0');
	lcd_w_dat(TEM_SIGN_ADDR);



	lcd_pos(0x40);
	i=0;
	while(rh_start_str[i] != '\0')
	{
		lcd_w_dat(rh_start_str[i]);
		i++;
	}
	lcd_w_dat(' ');
	lcd_w_dat('0');
	lcd_w_dat('0');
	lcd_w_dat('.');
	lcd_w_dat('0');
	lcd_w_dat('%');

}
void lcd_update_TH()
{
	lcd_pos(0x6);
	for(i=0;i<TEM_LEN;i++)
		lcd_w_dat(tem_str[i]);

	lcd_pos(0x47);
	for(i=0;i<RH_LEN;i++)
		lcd_w_dat(rh_str[i]);
}