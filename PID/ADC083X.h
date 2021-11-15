//==============================================================================
//2005-03-28...2005-03-29
//ADC0834模块的C51程序头文件
//File Name=ADC083X.h
//==============================================================================
//#include "W78E52.h"
//#include "Public.h"
#include <reg51.h>
#include <intrins.h>


#ifndef    _ADC083X_H_
#define _ADC083X_H_

//芯片类型号的定义
#define ADC0831    0
#define ADC0832    1
#define ADC0834    2
#define ADC0838    3

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//以下的芯片类型号和后面相应的硬件引脚需要按照实际的定义！
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#define TYPE_VAL    ADC0832        

#define _NOP5            _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

#if TYPE_VAL == ADC0838
    //本模块的引脚定义
    sbit HD_ADC083X_CS    =P1^3;
    sbit HD_ADC083X_DO    =P1^2;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^1;
    sbit HD_ADC083X_SARS  =P3^3;
        
    //操作引脚的宏定义
    //数据输入线,在时钟上升沿移入器件
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5
    
    #define SET_ADC083X_SARS HD_ADC083X_SARS =1; _NOP5
    #define CLR_ADC083X_SARS HD_ADC083X_SARS =0; _NOP5
        
  #elif  TYPE_VAL ==ADC0834   //测试通过
    //本模块的引脚定义
    sbit HD_ADC083X_CS    =P1^2;
    sbit HD_ADC083X_DO    =P1^5;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^4;
    sbit HD_ADC083X_SARS  =P1^1;
        
    //操作引脚的宏定义
    //数据输入线,在时钟上升沿移入器件
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5
    
    #define SET_ADC083X_SARS HD_ADC083X_SARS =1
    #define CLR_ADC083X_SARS HD_ADC083X_SARS =0

#elif    TYPE_VAL =ADC0832        //测试通过
    //本模块的引脚定义
    sbit HD_ADC083X_CS    =P1^3;
    sbit HD_ADC083X_DO    =P1^2;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^1;
        
    //操作引脚的宏定义
    //数据输入线,在时钟上升沿移入器件
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5

#else    //缺省时为ADC0831
    //本模块的引脚定义
    sbit HD_ADC083X_CS    =P2^5;
    sbit HD_ADC083X_DO    =P2^7;
    sbit HD_ADC083X_CLK    =P2^6;

#endif	
    
//操作引脚的宏定义的公共部分
//片选信号,低电平有效
#define SET_ADC083X_CS    HD_ADC083X_CS =1; _NOP5
#define CLR_ADC083X_CS    HD_ADC083X_CS =0; _NOP5
    
#define SET_ADC083X_DO    HD_ADC083X_DO =1; _NOP5
#define CLR_ADC083X_DO    HD_ADC083X_DO =0; _NOP5
        
//时钟线,外部主机: 时钟低电平时送数据位,时钟高电平时读数据位
#define SET_ADC083X_CLK    HD_ADC083X_CLK =1; _NOP5
#define CLR_ADC083X_CLK    HD_ADC083X_CLK =0; _NOP5

//数据输出线,在时钟下降沿移出器件
#define    JUDGE_ADC083X_DO    HD_ADC083X_DO
#define JUDGE_ADC083X_SARS    HD_ADC083X_SARS
//-----------------------------------------------------------------------------

//函数的说明
void adc083x_init(void);
unsigned char adc083x_do_one_change(unsigned char chanel);
#endif

//End Of File

