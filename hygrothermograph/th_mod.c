#include "th_mod.h"

extern unsigned char u8_temp;
extern unsigned char u8_data;
extern unsigned char u8_Tem_H;
extern unsigned char u8_Tem_L;
extern unsigned char u8_Rh_H;
extern unsigned char u8_Rh_L;
extern unsigned char u8_CRC;
extern unsigned char u8_flag;

sbit P01 = P0^1;
sbit Led_crc = P1^6;

void get_RH()
{
	P01 = 0;
	delay(18);
	P01 = 1;
	delay10us();
	delay10us();

	delay10us();
	delay10us();
	P01 = 1;
	if(!P01)
	{
		u8_flag = 2;
		while((!P01) && u8_flag++) ;//wait until P01 is high
		u8_flag = 2;
		while((P01) && u8_flag++) ;//wait while P01 is high

		getOneByte();
		u8_Rh_H = u8_data;
		getOneByte();
		u8_Rh_L = u8_data;
		getOneByte();
		u8_Tem_H = u8_data;
		getOneByte();
		u8_Tem_L = u8_data;
		getOneByte();	
		u8_CRC = u8_data;
		
		P01 = 1;	
	}

}
void getOneByte()
{
	u8_data = 0;
	for(i=0;i<8;i++)
	{
		u8_flag = 2;
		while((!P01) && u8_flag++) ;
		delay10us();
		delay10us();
		delay10us();
		u8_temp =0;
		if(P01 == 1)
			u8_temp = 1;
		u8_flag = 2;
		while((P01) && u8_flag++) ;
		if(u8_flag == 1)
			break;///out of time
		u8_data <<= 1 ;
		u8_data |= u8_temp;
	 }
}

void setupRH()
{
	unsigned int tem_temp;//´æ´¢10±¶ÎÂ¶È¾ø¶ÔÖµ
	unsigned int rh_temp; //´æ´¢10±¶Êª¶È

	//crc check
	u8_temp = u8_Tem_H + u8_Tem_L + u8_Rh_H + u8_Rh_L;
	if(u8_temp != u8_CRC)
	{
		for(i=0;i<TEM_LEN;i++)
			tem_str[i] = '0';
		for(i=0;i<RH_LEN;i++)
			rh_str[i]='0';
		Led_crc = ~Led_crc;
		return ;
	}

//	u8_Tem_H = 0x80;
//	u8_Tem_L = 0X0f;
//	u8_Rh_H = 0x0;
//	u8_Rh_L = 0x0f;


	rh_temp =  u8_Rh_H*256 + u8_Rh_L;
	tem_temp = (u8_Tem_H & 0x7f)*256 + u8_Tem_L;
	
	if((u8_Tem_H&0x80) == 0)
		tem_str[0] = ' ';
	else
		tem_str[0] = '-';

	if(tem_temp/100 == 0)
		tem_str[1] = ' ';
	else
		tem_str[1] = '0'+tem_temp/100;

//	if((tem_temp/10%10) == 0)
//		tem_str[2] = '0';
//	else
	tem_str[2] = '0'+tem_temp/10%10;
	tem_str[3] = '.';
	tem_str[4] = '0'+tem_temp%10;
	
	if(rh_temp/100 == 0)
		rh_str[0] = ' ';
	else
		rh_str[0] = '0'+rh_temp/100;
			
	rh_str[1] = '0'+rh_temp/10%10;
	rh_str[2] = '.';
	rh_str[3] = '0'+rh_temp%10;
}