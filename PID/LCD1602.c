#include "LCD1602.h"
#include <intrins.h>
//�ڲ������������ļ��ڿɵ���
uint8_t row=0,cow=0;
code uint8_t DDRAM[]={0x80,0xC0};
void delay()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

static void Busy_Wait()
{
	uint8_t LCD_Status;
	do
	{
		DATA=0xFF;
		EN=0;RS=0;RW=1;
		EN=1;LCD_Status=DATA;
		EN=0;
	}
	while(LCD_Status&0x80);
	//while(0);
}
static void Write_LCD_Command(uint8_t cmd)
{
	Busy_Wait();
	EN=0;RS=0;RW=0;
	DATA=cmd;
	EN=1;_nop_();EN=0;
}
static void Write_LDC_Data(uint8_t dat)
{
	Busy_Wait();
	EN=0;RS=1;RW=0;
	DATA=dat;
	EN=1;_nop_();EN=0;
}
//����ת����һ��
static void LCD_Next()
{
	row++;
	if(row == 16)
	{
		cow++;
		cow = cow&0x01;
	}
	row = row&0x0F;
}


//�����ӿ�
void LCD_Init()
{
	Write_LCD_Command(0x38);delay();
	Write_LCD_Command(0x01);delay();
	Write_LCD_Command(0x06);delay();
	Write_LCD_Command(0x0C);delay();
}

// - - ������ʾλ��
void LCD_setCursor(uint8_t x,uint8_t y)
{
	if((x>=16) || (y>=2)) return;
	row = x;
	cow = y;
	Write_LCD_Command(DDRAM[y]|x);
}
void LCD_gohome()
{
	LCD_setCursor(0,0);
}
void LCD_Clear()
{
	Write_LCD_Command(0x01);
}
//��ָ��λ������һ���ַ�
void LCD_putchar(uint8_t x,uint8_t y,uint8_t dat) 
{
	LCD_setCursor(x,y);
	Write_LDC_Data(dat);
}
//��ָ��λ�����һ���ַ���
void LCD_PutString(uint8_t x,uint8_t y,uint8_t *str)
{
	uint8_t i=0;
	LCD_setCursor(x,y);
	 for(i=0;str[i]!='\0';i++)
	{
		Write_LDC_Data(str[i]);
		LCD_Next();
	}
}
//�߼��ӿ�
void LCD_write(uint8_t dat)//�Զ����е�д��һ���ַ���
{
	if(row == 0)LCD_setCursor(row,cow);
	if(dat == 0x0A)
	{
		cow = ((++cow)%2);
		LCD_setCursor(0,cow);
		return;
	}
	LCD_Next();
	Write_LDC_Data(dat);
}
//�Զ����е��ַ�����ӡ
void LCD_print(uint8_t *s)
{
	while(*s!='\0')
	{
	LCD_write(*s);
	s++;
	}
}

/******printf�ض���LCD1602*******/
char putchar(char c)
{
    LCD_write(c);
    return c;
}