#ifndef __LCD_H__
#define __LCD_H__

#include "common.h"

typedef bit Boolean;


sbit RS = P0^7;
sbit RW = P0^6;
sbit EN = P0^5;

#define TEM_SIGN_ADDR 0x00


void lcd_init();
void lcd_TH_init();
void lcd_update_TH();

#endif