#ifndef _1602_H_
#define _1602_H_
#include "reg51.h"



#define DATA P0
/*****************************
Author:Suaig
Time:15-7-26
�汾1.0
���������ӿ�ʵ��
****************************/


/*****************************
Author:Suaig
Time:17-5-19
�汾2.0

����߼��ӿڣ����Ľ���װ
****************************/
typedef unsigned long uint32_t;
typedef unsigned int uint16_t;
typedef unsigned char uint8_t;
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;



void LCD_Init();
void LCD_PutString(uint8_t x,uint8_t y,uint8_t *str);
void LCD_setCursor(uint8_t x,uint8_t y);
void LCD_Clear();
void LCD_gohome();
void LCD_putchar(uint8_t x,uint8_t y,uint8_t dat);
void LCD_PutString(uint8_t r,uint8_t c,uint8_t *str);

//�߼��ӿ�
void LCD_write(uint8_t dat);
void LCD_print(uint8_t *s);

#endif
