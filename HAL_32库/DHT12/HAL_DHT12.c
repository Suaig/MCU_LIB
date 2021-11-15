#include "HAL_DHT12.H"


void DHT12_Init(HAL_DHT12_TypeStruct *hdht12)
{
	IIC_Init(&hdht12->myDHT12);
}
void DHT12_Read(HAL_DHT12_TypeStruct *hdht12)
{
		uint8_t dat[5],sum=0,i;
	 IIC_Start(&hdht12->myDHT12);  
	 IIC_Send_Byte(&hdht12->myDHT12,0xB8);	   //发送写命令//发送器件地址0xB8,写数据 
	 IIC_Wait_Ack(&hdht12->myDHT12);
			
   IIC_Send_Byte(&hdht12->myDHT12,0x00);//发送地址
	 IIC_Wait_Ack(&hdht12->myDHT12);

	 IIC_Start(&hdht12->myDHT12);  	 	   
	 IIC_Send_Byte(&hdht12->myDHT12,0xB9); //进入接收模式			   
	 IIC_Wait_Ack(&hdht12->myDHT12);	 
	 for(i=0;i<4;i++)
	{
			dat[i]=IIC_Read_Byte(&hdht12->myDHT12,1);//读前四个，发送ACK
			sum += dat[i];
	}
 	dat[i]=IIC_Read_Byte(&hdht12->myDHT12,0);//读第5个发送NACK
	IIC_Stop(&hdht12->myDHT12);//产生一个停止条件
	if(sum == dat[4])
	{
		hdht12->Temp = (float)dat[2] + (float)dat[3]/100;
		hdht12->Humi = (float)dat[0] + (float)dat[1]/100; 
	}
	else
	{
		return;
	}
	
	
}
float DHT12_GetHumi(HAL_DHT12_TypeStruct *hdht12)
{
	return hdht12->Humi;
}
float DHT12_GetTemp(HAL_DHT12_TypeStruct *hdht12)
{
	return hdht12->Temp;
}
