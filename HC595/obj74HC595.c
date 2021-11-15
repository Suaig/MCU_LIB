#include "obj74HC595.h"

/************************************
@��������:ģ��SPI�����ݷ��͵�595����λ�Ĵ�����
@INPUT:uint8_t��ָ�룬���Դ������֣�Ҳ���Դ����飬����ֽ�,size_t �����ֽ���,output �Ƿ������������
@OUTPUT:NULL
@
@
************************************/
SPI595_TypeStruct* HAL_Init_SPI595(SPI595_TypeStruct * obj,hc595_cb	cb)
{
	obj->myhc595 = cb;
	obj->myhc595(obj,MSG_HC_INIT,0);//��ʼ��
	return obj;
}
void HAL_OBJ595_Sendbytes(SPI595_TypeStruct * obj,uint8_t *pdate,size_t num,bool output)
{
	uint8_t temp=0,i,j;
	//SH_CP = 1;//̧�����ߣ�����ʱ��Ϊ1,��ʼ��������������
	
	obj->myhc595(obj,MSG_SH_CP,1);//SH_CP����Ϊ��
	for(i  = 0;i < num;i++)
	{
		temp = *(pdate + i);
		for(j = 0;j < 8;j++)
		{
			obj->myhc595(obj,MSG_SH_CP,0);
			//51��
//			temp <<= 1;
//			CY == 1 ? obj->Set_DS() : obj->Reset_DS();
			//��׼C��
			(temp&0x80) ? obj->myhc595(obj,MSG_ST_DS,1) : obj->myhc595(obj,MSG_ST_DS,0);
			 temp <<= 1;
			//GPIO_WritePin(obj->DS_Port,obj->DS_PIN,CY == 1 ? (HIGH):(LOW));
			obj->myhc595(obj,MSG_SH_CP,1);//SH_CP����Ϊ��
		}
	}
	//SH_CP = 1;//�ͷ�����
	obj->myhc595(obj,MSG_SH_CP,1);//SH_CP����Ϊ��
	if(output == true)
	{
		obj->myhc595(obj,MSG_ST_CP,1);//SH_CP����Ϊ��
		obj->myhc595(obj,MSG_ST_CP,0);//SH_CP����Ϊ��
		obj->myhc595(obj,MSG_ST_CP,1);//SH_CP����Ϊ��
	}
}
