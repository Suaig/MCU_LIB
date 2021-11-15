#include "obj_printf.h"

void new_frame_print(obj_frame *slf,putchar_cb ptcb) REENTRANT
{
	slf->ptc = ptcb;
}
void obj_printstr(obj_frame *slf,char *str)
{
     while(*str)
     {
         slf->ptc(slf,*str++);
     }
}
void obj_printbin(obj_frame *slf,uint8_t bindate) REENTRANT
{
	//slf->ptc(slf,'0');
	//slf->ptc(slf,'b');//开头
	while(bindate)
	{
		 slf->ptc(slf,((bindate & 0x80)>>7)+'0');
			bindate <<= 1;
	}
}
void obj_printint(obj_frame *slf,int16_t dec) REENTRANT//类似itoa
{
	uint8_t temp[5] = {0},i=4;//缓冲，待会逆序输出
	if((dec & 0x8000))
	{
		slf->ptc(slf,'-');
	}
	dec &= ~(0x8000);//去符号
	while(dec)
	{
		temp[i] = dec%10;
		if(i != 0)i--;
		dec/=10;
	}
	while(!temp[i])
	{
		i++;
	}
	while(i<5)
	{
		 slf->ptc(slf,temp[i]+'0');
		i++;
	}
}
void obj_printhex(obj_frame *slf,uint8_t hex) REENTRANT
{
	while(hex)
	{
		switch(hex & 0xF0)
		{
			case 0x00:
			case 0x10:
			case 0x20:
			case 0x30:
			case 0x40:
			case 0x50:
			case 0x60:
			case 0x70:
			case 0x80:
			case 0x90:
			slf->ptc(slf,(hex>>4)+'0');
			break;
			case 0xA0:
			case 0xB0:
			case 0xC0:
			case 0xD0:
			case 0xE0:
			case 0xF0:
			slf->ptc(slf,((hex>>4)-10)+'A');
			break;
		}
		hex <<=4 ;
	}
}
void obj_printfloat(obj_frame *slf,float flt) REENTRANT
{
	int16_t tempint = (int16_t)flt;//取整数部分
	int16_t tempfloat = (int16_t)((flt - (float)tempint)*1000);
	obj_printint(slf,tempint);
	slf->ptc(slf,'.');
	if(tempfloat < 10)
	{
		slf->ptc(slf,'0');slf->ptc(slf,'0');slf->ptc(slf,tempfloat+'0');
		return;
	}
	if(tempfloat < 100)
	{
		slf->ptc(slf,'0');obj_printint(slf,tempfloat);
		return;
	}
	obj_printint(slf,tempfloat);
}
void obj_printf(obj_frame *slf,const char *format,...) REENTRANT
{
    va_list ap;
 
    va_start(ap,format);
    while(*format)
    {
      if(*format != '%')
			{
					slf->ptc(slf,*format);
					format++;
			}
			else if(*format == '%')
			{
					format++;
					switch(*format)
					{
							case 'c':
				{
						char val_ch = va_arg(ap,int);
						slf->ptc(slf,val_ch);
						format++;
						break;
				}
		 
				case 'd':
				{
						int val_int = va_arg(ap,int);
						obj_printint(slf,val_int);
						format++;
						break;
				}
		 
				case 's':
				{
						char * val_str = va_arg(ap,char *);
						obj_printstr(slf,val_str);
						format++;
						break;
				}
		 
				case 'f':
				{
						float val_flt = va_arg(ap,double);
						obj_printfloat(slf,val_flt);
						format++;
						break;
				}
				case 'x':
				{
						uint8_t val_flt = (uint8_t)va_arg(ap,int);
						obj_printhex(slf,val_flt);
						format++;
						break;
				}
				case 'b':
				{
					uint8_t val_flt = (uint8_t)va_arg(ap,int);
					obj_printbin(slf,val_flt);
					format++;
					break;
				}
				default :
				{
						slf->ptc(slf,*format);
						format++;
				}
					}
			}
			//else if(*format)
		}
    va_end(ap); 
}
