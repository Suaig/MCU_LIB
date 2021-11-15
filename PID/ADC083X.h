//==============================================================================
//2005-03-28...2005-03-29
//ADC0834ģ���C51����ͷ�ļ�
//File Name=ADC083X.h
//==============================================================================
//#include "W78E52.h"
//#include "Public.h"
#include <reg51.h>
#include <intrins.h>


#ifndef    _ADC083X_H_
#define _ADC083X_H_

//оƬ���ͺŵĶ���
#define ADC0831    0
#define ADC0832    1
#define ADC0834    2
#define ADC0838    3

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//���µ�оƬ���ͺźͺ�����Ӧ��Ӳ��������Ҫ����ʵ�ʵĶ��壡
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#define TYPE_VAL    ADC0832        

#define _NOP5            _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

#if TYPE_VAL == ADC0838
    //��ģ������Ŷ���
    sbit HD_ADC083X_CS    =P1^3;
    sbit HD_ADC083X_DO    =P1^2;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^1;
    sbit HD_ADC083X_SARS  =P3^3;
        
    //�������ŵĺ궨��
    //����������,��ʱ����������������
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5
    
    #define SET_ADC083X_SARS HD_ADC083X_SARS =1; _NOP5
    #define CLR_ADC083X_SARS HD_ADC083X_SARS =0; _NOP5
        
  #elif  TYPE_VAL ==ADC0834   //����ͨ��
    //��ģ������Ŷ���
    sbit HD_ADC083X_CS    =P1^2;
    sbit HD_ADC083X_DO    =P1^5;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^4;
    sbit HD_ADC083X_SARS  =P1^1;
        
    //�������ŵĺ궨��
    //����������,��ʱ����������������
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5
    
    #define SET_ADC083X_SARS HD_ADC083X_SARS =1
    #define CLR_ADC083X_SARS HD_ADC083X_SARS =0

#elif    TYPE_VAL =ADC0832        //����ͨ��
    //��ģ������Ŷ���
    sbit HD_ADC083X_CS    =P1^3;
    sbit HD_ADC083X_DO    =P1^2;
    sbit HD_ADC083X_CLK   =P1^0;
    sbit HD_ADC083X_DI    =P1^1;
        
    //�������ŵĺ궨��
    //����������,��ʱ����������������
    #define SET_ADC083X_DI    HD_ADC083X_DI =1; _NOP5
    #define CLR_ADC083X_DI    HD_ADC083X_DI =0; _NOP5

#else    //ȱʡʱΪADC0831
    //��ģ������Ŷ���
    sbit HD_ADC083X_CS    =P2^5;
    sbit HD_ADC083X_DO    =P2^7;
    sbit HD_ADC083X_CLK    =P2^6;

#endif	
    
//�������ŵĺ궨��Ĺ�������
//Ƭѡ�ź�,�͵�ƽ��Ч
#define SET_ADC083X_CS    HD_ADC083X_CS =1; _NOP5
#define CLR_ADC083X_CS    HD_ADC083X_CS =0; _NOP5
    
#define SET_ADC083X_DO    HD_ADC083X_DO =1; _NOP5
#define CLR_ADC083X_DO    HD_ADC083X_DO =0; _NOP5
        
//ʱ����,�ⲿ����: ʱ�ӵ͵�ƽʱ������λ,ʱ�Ӹߵ�ƽʱ������λ
#define SET_ADC083X_CLK    HD_ADC083X_CLK =1; _NOP5
#define CLR_ADC083X_CLK    HD_ADC083X_CLK =0; _NOP5

//���������,��ʱ���½����Ƴ�����
#define    JUDGE_ADC083X_DO    HD_ADC083X_DO
#define JUDGE_ADC083X_SARS    HD_ADC083X_SARS
//-----------------------------------------------------------------------------

//������˵��
void adc083x_init(void);
unsigned char adc083x_do_one_change(unsigned char chanel);
#endif

//End Of File

