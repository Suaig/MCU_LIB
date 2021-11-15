#ifndef __IIC_H
#define __IIC_H
#include "stm32f0xx_hal.h"
#include "HAL_Delay.h"
typedef struct
{
	GPIO_TypeDef* I2C_SDA_GPIOx;
	uint16_t      I2C_SDA_GPINx;
	GPIO_TypeDef* I2C_SCL_GPIOx;
	uint16_t      I2C_SCL_GPINx;
}HAL_SOFE_I2C_TypeStruct;

void SDA_IN(HAL_SOFE_I2C_TypeStruct *hi2c);
void SDA_OUT(HAL_SOFE_I2C_TypeStruct *hi2c);

//IIC所有操作函数
void IIC_Init(HAL_SOFE_I2C_TypeStruct *hi2c);                //初始化IIC的IO口				 
void IIC_Start(HAL_SOFE_I2C_TypeStruct *hi2c);				//发送IIC开始信号
void IIC_Stop(HAL_SOFE_I2C_TypeStruct *hi2c);	  			//发送IIC停止信号
void IIC_Send_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t ack);//IIC读取一个字节


uint8_t IIC_Wait_Ack(HAL_SOFE_I2C_TypeStruct *hi2c); 				//IIC等待ACK信号

void IIC_Ack(HAL_SOFE_I2C_TypeStruct *hi2c);					//IIC发送ACK信号
void IIC_NAck(HAL_SOFE_I2C_TypeStruct *hi2c);				//IIC不发送ACK信号
#endif
















