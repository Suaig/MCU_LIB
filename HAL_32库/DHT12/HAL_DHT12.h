#ifndef _HAL_DHT12_H_
#define _HAL_DHT12_H_

#include "HAL_DHT12.H"
#include "HAL_I2C.H"


typedef struct
{
	HAL_SOFE_I2C_TypeStruct myDHT12;
	float Temp;
	float Humi;
}HAL_DHT12_TypeStruct;



void DHT12_Init(HAL_DHT12_TypeStruct *hdht12);
void DHT12_Read(HAL_DHT12_TypeStruct *hdht12);

float DHT12_GetHumi(HAL_DHT12_TypeStruct *hdht12);
float DHT12_GetTemp(HAL_DHT12_TypeStruct *hdht12);



#endif

