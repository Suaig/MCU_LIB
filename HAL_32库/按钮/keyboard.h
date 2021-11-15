#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
/********************************
51���̼���ɨ��
״̬����ʶ�𵥸��������£������������Ѿ��ͷ�


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
//keymode ��ָ���̰����Ǹߵ�ƽ���ǵ͵�ƽ






typedef struct
{

	GPIO_TypeDef* GPIO;
	uint16_t pin;
	GPIO_PinState oldkey;	//δ����ʱ��ʼ�ܽŵ�ƽ
	GPIO_PinState keymode;//δ����ʱ�Ǹߵ�ƽ���ǵ͵�ƽ 
}Keyscan_Type; //��������ṹ��

Key_State keyscan(Keyscan_Type* a);                        //����ɨ��


#endif
