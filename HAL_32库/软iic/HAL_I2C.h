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

//IIC���в�������
void IIC_Init(HAL_SOFE_I2C_TypeStruct *hi2c);                //��ʼ��IIC��IO��				 
void IIC_Start(HAL_SOFE_I2C_TypeStruct *hi2c);				//����IIC��ʼ�ź�
void IIC_Stop(HAL_SOFE_I2C_TypeStruct *hi2c);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t ack);//IIC��ȡһ���ֽ�


uint8_t IIC_Wait_Ack(HAL_SOFE_I2C_TypeStruct *hi2c); 				//IIC�ȴ�ACK�ź�

void IIC_Ack(HAL_SOFE_I2C_TypeStruct *hi2c);					//IIC����ACK�ź�
void IIC_NAck(HAL_SOFE_I2C_TypeStruct *hi2c);				//IIC������ACK�ź�
#endif
















