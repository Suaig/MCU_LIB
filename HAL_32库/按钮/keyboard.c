#include "keyboard.h"

Key_State keyscan(Keyscan_Type* a)
{
	GPIO_PinState key=HAL_GPIO_ReadPin(a->GPIO,a->pin);
	Key_State returnkey;
	
	if(a->oldkey == key)
	{
		(key == a->keymode)?(returnkey=KEY_DOWNED):(returnkey=KEY_UPED);
	}
	else
	{
		(key == a->keymode)?(returnkey=KEY_DOWNING):(returnkey=KEY_UPING);
	}
	a->oldkey = key;
	return returnkey;
}
