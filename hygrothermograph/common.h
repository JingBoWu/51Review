#ifndef __COMMON_H__
#define __COMMON_H__

#include<reg52.h>
#include<intrins.h>

#define TEM_LEN 5
#define RH_LEN 4
extern unsigned char tem_str[TEM_LEN];
extern unsigned char rh_str[RH_LEN];
extern unsigned char i;

void delay10us();
void delay(unsigned char ms);
void ask_for_data();


#endif



