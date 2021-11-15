/**********************************************函数定义***************************************************** 
* 功能模块: 伪多线程,
						开一个伪多线程需要花费6字节额外RAM以及46ROM
* 功    能: 使用定时器调度和状态机实现的伪多线程，可以在任何支持C编译器的单片机上移植
* 作    者: Suaig
* 日    期: 2017/07/01
************************************************************************************************************/ 

#include "main.h"
#include "stm32f1xx_hal.h"
//#include "dac.h"
//#include "gpio.h"
#define FSEMX            0u


/*******************任务调度器*****************************/
#define _SS static uint32_t ddtime = 0,Task_Tick = 0;static uint16_t _lc=0;if((HAL_GetTick()-Task_Tick) >= ddtime){Task_Tick = HAL_GetTick();switch(_lc){default:
#define _EE break;}}
//等待N个时间片 每个时间片初始值是1ms，可以重新对Timer0初始化得到其他时间片长度，建议时间片长度不少于1000个机器周期，否则任务调度花费会大大增加！
#define WaitTick(a) _lc =  __LINE__;ddtime = a;return 255;case __LINE__:_lc = 0;ddtime=0;

/*******************信号量*****************************/
typedef uint16_t SEM;
//初始化信号量
#define InitSEM(s) s = 1
//发送信号量
#define SendSem(s) s = 0
//无时长等待信号量
#define WaitSem(s) while(s == 1){WaitTick(0);}s == 0 ? s = 1 : (s)
//清除信号量
#define ClearSem(s) s == 0 ? s = 1 : (s) 


#if FSEMX > 0u
SEM WaitSemX(SEM *s,uint16_t t);//带超时的等待信号量
#endif



/***********************************************************
伪线程举例：
uint8_t LED2_Task()//LED2任务
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
