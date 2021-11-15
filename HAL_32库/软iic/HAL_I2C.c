#include "HAL_I2C.h"

/********************************************************************/
/* ���������ѧϰ�ο���δ�������������������κ���ҵ��;  			        */
/* ������ΪFuhome������Զ�̿����ն˾�ϵ��ר�ó���              	      */
/* ������Ӳ��ƽ̨  ����W5500+STM32F103C8T6 64K+20K					          */
/* ������̳��www.fuhome.net/bbs/						        	                */
/* ��Ƭ��������ã�I/O�ڶ��壬��ʱ�������ڣ��жϵȳ�ʼ������ 	          */
/* ����������Ӳ���豸����fuhome.net ƽ̨����Զ�̿��ƣ��ֻ�APP/΢��/WEB */ 
/* �汾��v1.2 2016��6��30��						       			 	                */
/* �����ܶ�										       			 	                        */
/* ���ڸ��£������ע�������ţ����������룬����	     			 	          */
/* Copyright fuhome.net δ��֮�� ʵ���ң��ÿƼ���������				        */
/********************************************************************/


void SDA_IN(HAL_SOFE_I2C_TypeStruct *hi2c)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = hi2c->I2C_SDA_GPINx;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(hi2c->I2C_SDA_GPIOx,&GPIO_InitStructure);
}
void SDA_OUT(HAL_SOFE_I2C_TypeStruct *hi2c)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = hi2c->I2C_SDA_GPINx;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(hi2c->I2C_SDA_GPIOx,&GPIO_InitStructure);
}



//��ʼ��IIC
void IIC_Init(HAL_SOFE_I2C_TypeStruct *hi2c)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if((hi2c->I2C_SDA_GPIOx == GPIOA) || (hi2c->I2C_SCL_GPIOx == GPIOA))
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}else if((hi2c->I2C_SDA_GPIOx == GPIOB) || (hi2c->I2C_SCL_GPIOx == GPIOB))
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}else if((hi2c->I2C_SDA_GPIOx == GPIOC) || (hi2c->I2C_SCL_GPIOx == GPIOC))
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}else if((hi2c->I2C_SDA_GPIOx == GPIOD) || (hi2c->I2C_SCL_GPIOx == GPIOD))
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}else if((hi2c->I2C_SDA_GPIOx == GPIOF) || (hi2c->I2C_SCL_GPIOx == GPIOF))
	{
		__HAL_RCC_GPIOF_CLK_ENABLE();
	}
	GPIO_InitStructure.Pin = hi2c->I2C_SCL_GPINx;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	//GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(hi2c->I2C_SCL_GPIOx,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.Pin =  hi2c->I2C_SDA_GPINx;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	//GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(hi2c->I2C_SDA_GPIOx,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
}
//����IIC��ʼ�ź�
void IIC_Start(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	SDA_OUT(hi2c);     //sda�����
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(4);
 	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	delay_us(4);
}	  
//����IICֹͣ�ź�
void IIC_Stop(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	SDA_OUT(hi2c);//sda�����
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
 	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
	delay_us(4);									   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	uint8_t ucErrTime=0;
	SDA_IN(hi2c);      //SDA����Ϊ����  
	
	delay_us(4);	   
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(4);	 
	while(HAL_GPIO_ReadPin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop(hi2c);
			return 1;
		}
		delay_us(1);
	}
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
  delay_us(50);	
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	SDA_OUT(hi2c);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
}
//������ACKӦ��		    
void IIC_NAck(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	SDA_OUT(hi2c);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t txd)
{                        
    uint8_t t;   
	  SDA_OUT(hi2c); 	    
    HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
    //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80) == 0x00)
		{
			HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
		}
    txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
		delay_us(2); 
		HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t ack)
{
	unsigned char i,receive=0;
	SDA_IN(hi2c);//SDA����Ϊ����
    for(i=0;i<8;i++ )
	 {
        HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET); 
        delay_us(50);
				HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
		    delay_us(50);
        receive<<=1;
		if(HAL_GPIO_ReadPin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx))receive++;		
    }					 
    if (!ack)
        IIC_NAck(hi2c);//����nACK
    else
        IIC_Ack(hi2c); //����ACK   
    return receive;
}



























