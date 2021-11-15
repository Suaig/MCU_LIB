#ifndef _HAL_DELAY_H_
#define _HAL_DELAY_H_
#include "stm32f0xx_hal.h"
void delay_init(void);//在系统时钟配置完成之后调用
void delay_us(uint32_t nus);

#endif

