#ifndef _DHT11_H_
#define _DHT11_H_
#include "main.h"
/*************************************************************************************************************************************
@ģ�鹦�ܣ����DHT11������
@����:Suaig
@ʱ��:2018-2-1
@����˵��:�������ڴ�ͳ51�Ͽ��ܲ�����������������51��Ƭ����Ƶ�ͣ��Ҷ��ں���ָ����õĶ��ط�ʽ��ʹ
@				 ����⿪����(��Ҫ��ʱ���ϵ�)���µ�����������Ҫ�ϸ�ʱ���������������������ʵ����
@			 STC15 12M��Ƶ���Ժܺ����� ������AT89C51 120M��Ƶ�¿�������ʹ��
@      stm32 avr����
*************************************************************************************************************************************/
#define REENTRANT
//#define REENTRANT reentrant   //һЩ����Ĵ�����������Ҫ�������ʶ����ջ�ṹ������Ͷ���Ϊ��

#ifdef __cplusplus //C++����
extern "C" {
#endif
	
	
enum{
	DHT11_MSG_2S_DELAY =40,
	DHT11_MSG_18MS_DELAY,
	DHT11_MSG_1MS_DELAY,
	DHT11_MSG_30US_DELAY,
	DHT11_MSG_READ_SDA,
	DHT11_MSG_SDA_HIGH,
	DHT11_MSG_SDA_LOW,
};


typedef struct DHT11_struct DHT11_t;
/*
	����Ļص��������������һЩ��Ӳ����صĲ���
	DHT11_t *dht ָ��DHT11����Ľṹ��ָ��
	uint8_t msg ��Ϣ����Ϣ������ʱ��IO������
*/
typedef uint8_t (*dht11_msg_cb)(DHT11_t *dht, uint8_t msg) REENTRANT;//����51���Ƕ�ջ�ܹ������ԣ�������һ���ֲ�����������R0-R9���д��ݣ�����Ҫʹ��ģ���ջ�����Ｔʹ��ģ���ջ


struct DHT11_struct
{
	uint8_t DHT11_RXD_Buff[5];
	dht11_msg_cb gpio_and_delay_cb;
	
};


/*
������DHT11�����ʼ��������ص������Ͷ���ָ��
����:
			DHT11_t *dht ָ��DHT11����Ľṹ��ָ��
			DHT11_msg_cb dht_cb �ص������ĺ���ָ��
			�������죺uint8_t (*DHT11_msg_cb)(DHT11_t *dht, uint8_t msg)
*/
void DHT11_Init(DHT11_t *dht,dht11_msg_cb dht_cb);//DHT11�����ʼ��������ص������Ͷ���ָ��
uint8_t DHT11_Read(DHT11_t *dht);									//DHT11����һ������
uint8_t DHT11_Fget(DHT11_t *dht,float *Humi,float *Temp);//��������֮��ʹ����������ĵ�һ��һλС���ĸ��������ݣ�
/*
��������������֮��ʹ����������ĵ�һ��int�����ݣ�
����:
			DHT11_t *dht ָ��DHT11����Ľṹ��ָ��
			int16_t *Humi    ���ڷ���ʪ�ȵ�16λ���ȵ��з������ε�ָ��
			int16_t *Temp    ���ڷ����¶ȵ�16λ���ȵ��з������ε�ָ��
*/
uint8_t DHT11_Iget(DHT11_t *dht,int16_t *Humi,int16_t *Temp);//��������֮��ʹ����������ĵ�һ��int�����ݣ�

/****************************************************
*	�ص�����ʾ��
*����������IO�Ķ�д���Լ�������ʱ�����ȿ������ֲ
*uint8_t DHT11_8C51_cb(DHT11_t *dht, uint8_t msg)
{
	//����δʹ��DHT11����ָ�룬��Ϊ������ֻ��Ҫȥ����һ��DHT11
	switch(msg)
	{
	case DHT11_MSG_2S_DELAY://�����ϵ��ʼ���ȶ�DHT11
		Delay2000ms();
	break;
	case DHT11_MSG_18MS_DELAY:
			Delay18ms();
	break;
	case DHT11_MSG_1MS_DELAY:
		Delay1ms();
	break;
	
	case DHT11_MSG_30US_DELAY:
		Delay30us();
	break;
	case DHT11_MSG_READ_SDA: 
		return (P3&0x01);
	break;
	case DHT11_MSG_SDA_HIGH:
				P3|=0x01;
	break;
	case DHT11_MSG_SDA_LOW:
				P3&=0xFE;
	break;
	default:return 0xFF;
	}
	return 0;
}
*
���������������ֶ�������Ƿ�ʽ1����ʽ2�����Ƕ�����һ�����Ʋ�ͬ�Ļص�������
uint8_t DHT11_8C51_cb(DHT11_t *dht, uint8_t msg)
{
	switch(msg)
	{
	case DHT11_MSG_2S_DELAY://�����ϵ��ʼ���ȶ�DHT11
		Delay2000ms();
	break;
	case DHT11_MSG_18MS_DELAY:
			Delay18ms();
	break;
	case DHT11_MSG_1MS_DELAY:
		Delay1ms();
	break;
	
	case DHT11_MSG_30US_DELAY:
		Delay30us();
	break;
	case DHT11_MSG_READ_SDA: 
	if(dht == &hdht1)    //������,��Ӳ������ĵط���Ҫ�ӣ���������дIO
	{
		return (P3&0x01);
	}
	else
	{
		return (P2&0x01);
	}
	break;
	case DHT11_MSG_SDA_HIGH:
				P3|=0x01;
	break;
	case DHT11_MSG_SDA_LOW:
				P3&=0xFE;
	break;
	default:return 0xFF;
	}
	return 0;
}
*****************************************************/
#ifdef __cplusplus
}
#endif
#endif