#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
/********************************
51键盘键盘扫描
状态机，识别单个按键按下，长按，弹起，已经释放


********************************/

#include "main.h"
#include "stm32f1xx_hal.h"
typedef enum
{
	KEY_DOWNED,
	KEY_DOWNING,
	KEY_UPED,
	KEY_UPING
}Key_State;





#define keymode GPIO_PIN_RESET 
//keymode 是指键盘按下是高电平还是低电平






typedef struct
{

	GPIO_TypeDef* GPIO;
	uint16_t pin;
	GPIO_PinState oldkey;	//未按下时初始管脚电平
	GPIO_PinState keymode;//未按下时是高电平还是低电平 
}Keyscan_Type; //按键对象结构体

Key_State keyscan(Keyscan_Type* a);                        //键盘扫描


#endif
