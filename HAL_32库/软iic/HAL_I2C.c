#include "HAL_I2C.h"

/********************************************************************/
/* 本程序仅供学习参考，未经作者允许，不得用于任何商业用途  			        */
/* 本程序为Fuhome互联网远程控制终端静系列专用程序              	      */
/* 适用于硬件平台  采用W5500+STM32F103C8T6 64K+20K					          */
/* 技术论坛：www.fuhome.net/bbs/						        	                */
/* 单片机相关配置，I/O口定义，定时器，串口，中断等初始化函数 	          */
/* 本程序用于硬件设备接入fuhome.net 平台进行远程控制（手机APP/微信/WEB */ 
/* 版本：v1.2 2016年6月30日						       			 	                */
/* 龙剑奋斗										       			 	                        */
/* 定期更新，敬请关注——开放，交流，深入，进步	     			 	          */
/* Copyright fuhome.net 未来之家 实验室，让科技融入生活				        */
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



//初始化IIC
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
//产生IIC起始信号
void IIC_Start(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	SDA_OUT(hi2c);     //sda线输出
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(4);
 	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	delay_us(4);
}	  
//产生IIC停止信号
void IIC_Stop(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	SDA_OUT(hi2c);//sda线输出
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_RESET);
 	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
	delay_us(4);
	HAL_GPIO_WritePin(hi2c->I2C_SDA_GPIOx,hi2c->I2C_SDA_GPINx,GPIO_PIN_SET);
	delay_us(4);									   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(HAL_SOFE_I2C_TypeStruct *hi2c)
{
	uint8_t ucErrTime=0;
	SDA_IN(hi2c);      //SDA设置为输入  
	
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
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t txd)
{                        
    uint8_t t;   
	  SDA_OUT(hi2c); 	    
    HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);//拉低时钟开始数据传输
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
		delay_us(2);   //对TEA5767这三个延时都是必须的
		HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_SET);
		delay_us(2); 
		HAL_GPIO_WritePin(hi2c->I2C_SCL_GPIOx,hi2c->I2C_SCL_GPINx,GPIO_PIN_RESET);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(HAL_SOFE_I2C_TypeStruct *hi2c,uint8_t ack)
{
	unsigned char i,receive=0;
	SDA_IN(hi2c);//SDA设置为输入
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
        IIC_NAck(hi2c);//发送nACK
    else
        IIC_Ack(hi2c); //发送ACK   
    return receive;
}



























