#include "common.h"
#include "lcd.h"
#include "clock.h"
#include "th_mod.h"

unsigned char tem_str[TEM_LEN];
unsigned char rh_str[RH_LEN];
unsigned char i;
unsigned char a=0;

unsigned char u8_temp;
unsigned char u8_data;

unsigned char u8_Tem_H;
unsigned char u8_Tem_L;
unsigned char u8_Rh_H;
unsigned char u8_Rh_L;
unsigned char u8_CRC;
unsigned char u8_flag;


void ask_for_data()
{
	get_RH();
	setupRH();
	lcd_update_TH();
}

void main()
{
	//delay10us();
	lcd_init();
	lcd_TH_init();

	init_clock_reg();
	init_clock_interrupt();
	reset_clock();
	while(1);
}