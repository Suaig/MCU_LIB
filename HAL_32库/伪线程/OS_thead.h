/**********************************************��������***************************************************** 
* ����ģ��: α���߳�,
						��һ��α���߳���Ҫ����6�ֽڶ���RAM�Լ�46ROM
* ��    ��: ʹ�ö�ʱ�����Ⱥ�״̬��ʵ�ֵ�α���̣߳��������κ�֧��C�������ĵ�Ƭ������ֲ
* ��    ��: Suaig
* ��    ��: 2017/07/01
************************************************************************************************************/ 

#include "main.h"
#include "stm32f1xx_hal.h"
//#include "dac.h"
//#include "gpio.h"
#define FSEMX            0u


/*******************���������*****************************/
#define _SS static uint32_t ddtime = 0,Task_Tick = 0;static uint16_t _lc=0;if((HAL_GetTick()-Task_Tick) >= ddtime){Task_Tick = HAL_GetTick();switch(_lc){default:
#define _EE break;}}
//�ȴ�N��ʱ��Ƭ ÿ��ʱ��Ƭ��ʼֵ��1ms���������¶�Timer0��ʼ���õ�����ʱ��Ƭ���ȣ�����ʱ��Ƭ���Ȳ�����1000���������ڣ�����������Ȼ��ѻ������ӣ�
#define WaitTick(a) _lc =  __LINE__;ddtime = a;return 255;case __LINE__:_lc = 0;ddtime=0;

/*******************�ź���*****************************/
typedef uint16_t SEM;
//��ʼ���ź���
#define InitSEM(s) s = 1
//�����ź���
#define SendSem(s) s = 0
//��ʱ���ȴ��ź���
#define WaitSem(s) while(s == 1){WaitTick(0);}s == 0 ? s = 1 : (s)
//����ź���
#define ClearSem(s) s == 0 ? s = 1 : (s) 


#if FSEMX > 0u
SEM WaitSemX(SEM *s,uint16_t t);//����ʱ�ĵȴ��ź���
#endif



/***********************************************************
α�߳̾�����
uint8_t LED2_Task()//LED2����
{
	_SS
	if(GPIO_ReadPin(GPIO_P3,GPIO_PIN_0) == LOW)
	{
		if(GPIO_ReadPin(GPIO_P3,GPIO_PIN_0) == LOW)
		{
			Menu == 3 ? (Menu = 0) : (Menu ++);
			while(GPIO_ReadPin(GPIO_P3,GPIO_PIN_0) == LOW)
			{
				WaitTick(10);
			}
		}
	}
	_EE
	return 0;
}
***********************************************************/
