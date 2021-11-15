#ifndef _OBJ_PRINTF_
#define _OBJ_PRINTF_

//功能：提供对象化的printf函数，有时候需要多个printf指向不同输出器的时候使用，独立于stdio.h里的printf，可以同时使用。
//作者：Suaig
//时间：2018/11/7
//PS:一个轻量化的printf，支持整数，小数，二进制数，16进制数的输出，不支持指定格式长度
//
#ifdef __cplusplus
	extern "C"{
#endif
		
#include "main.h"				
#include <stdarg.h>
		
//typedef unsigned char uint8_t;	
//typedef unsigned int uint16_t;
		
typedef struct _ojpf obj_frame;
typedef uint8_t (*putchar_cb)(obj_frame *slf,uint8_t dat) REENTRANT;
		

struct _ojpf
{
	putchar_cb ptc;
};

void new_frame_print(obj_frame *slf,putchar_cb ptcb) REENTRANT;
void obj_printf(obj_frame *slf,const char *format,...) REENTRANT;
void obj_printfloat(obj_frame *slf,float flt) REENTRANT;
void obj_printhex(obj_frame *slf,uint8_t hex) REENTRANT;
void obj_printint(obj_frame *slf,int16_t dec) REENTRANT;
void obj_printbin(obj_frame *slf,uint8_t bindate) REENTRANT;

#ifdef __cplusplus
}
#endif

#endif
