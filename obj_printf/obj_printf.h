#ifndef _OBJ_PRINTF_
#define _OBJ_PRINTF_

//���ܣ��ṩ���󻯵�printf��������ʱ����Ҫ���printfָ��ͬ�������ʱ��ʹ�ã�������stdio.h���printf������ͬʱʹ�á�
//���ߣ�Suaig
//ʱ�䣺2018/11/7
//PS:һ����������printf��֧��������С��������������16���������������֧��ָ����ʽ����
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
