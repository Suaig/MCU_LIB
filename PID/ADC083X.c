
//==============================================================================//2005-03-28...2005-03-29//ADC0834ģ���C51����Դ�ļ�//File Name=ADC083X.c//==============================================================================#include #include 
 
//==============================================================================
//2005-03-28...2005-03-29
//ADC0834ģ���C51����Դ�ļ�
//File Name=ADC083X.c
//==============================================================================
#include "ADC083X.h"

//�ⲿȫ�ֱ�����Ԥ����

//*******************************************************
//���:
//        HD_ADC083X_S01
//����:    
//        �˿ڳ�ʼ��
//����:    
//        ��
//���:    
//        ��
//********************************************************
void adc083x_init(void)
{
    SET_ADC083X_CS;
    SET_ADC083X_DO;
    CLR_ADC083X_CLK;

#if TYPE_VAL >=ADC0832
    SET_ADC083X_DI;
#endif

#if TYPE_VAL >=ADC0834
    SET_ADC083X_SARS;
#endif

}

//*******************************************************
//���:
//        HD_ADC083X_S02
//����:    
//        ����AD�����ֽ�
//����:    
//        chanel    ͨ�����Լ�����˫������ѡ��,����ֵ������ֵ���ƣ�
//            ����Чֵ��select�ֱ�ȡ���4��3��2λ��ʹ��
//            �����ֵ�μ�pdf�ĵ�!
//���:    
//        ADת���Ľ���ֽ�
//********************************************************
unsigned char adc083x_do_one_change(unsigned char chanel)
{
unsigned char data ad_val;
unsigned char data i;

    //ת��ǰ�ĳ�ʼ��
    SET_ADC083X_CS;
    CLR_ADC083X_CLK;
    SET_ADC083X_DO;
    
    CLR_ADC083X_CS;

//SARS���ŷǱ�Ҫʱ���Բ�ʹ��,�Խ�ʡ������Դ��
#if (TYPE_VAL==ADC0838)
	/*
    //chanel_.3    .2     .1    .0    =0000 ͨ��0+_ͨ��1-, 
=001 ͨ��2+_ͨ��3-,(˫�˷�ʽ)
    //    SGL/DIF ODD/SIGN SELECT    SELECT    =0010 ͨ��4+_ͨ��5-, 
=011 ͨ��6+_ͨ��7-,(˫�˷�ʽ)
    //                    =0100 ͨ��0-_ͨ��1+, 
=0101 ͨ��2-_ͨ��3+,(˫�˷�ʽ)
    //                    =0110 ͨ��4-_ͨ��5+, 
=0111 ͨ��6-_ͨ��7+,(˫�˷�ʽ)
    //                    =1000 ͨ��0+,    =1001 
ͨ��2+,(���˷�ʽ)
    //                    =1010 ͨ��4+,    =1011 
ͨ��6+,(���˷�ʽ)
    //                    =1100 ͨ��1+,    =1101 
ͨ��3+,(���˷�ʽ)
    //                    =1110 ͨ��5+,    =1111 
ͨ��7+,(���˷�ʽ)
*/

    //����/SE���Խӵ�,��ʹ������Ʒ����ֽڵ������ʱ���ܣ�

    chanel |=0x10;        //������ʼλ
    for(i=0; i<5; i++)
    {
        if( (chanel &0x10)!=0)
        {
            SET_ADC083X_DI;
        }
        else
        {
            CLR_ADC083X_DI;
        }
        SET_ADC083X_CLK;
        CLR_ADC083X_CLK;
        chanel <<=1;
    }

#elif (TYPE_VAL==ADC0834)
		/*
    //chanel_.2    .1     .0    =000 ͨ��0+_ͨ��1-, =001 ͨ��2+_ͨ
��3-,    (˫�˷�ʽ)
    //    SGL/DIF ODD/SIGN SELECT    =010 ͨ��0-_ͨ��1+, =011 ͨ��2-_ͨ
��3+,    (˫�˷�ʽ)
    //                =100 ͨ��0+,        =101 ͨ��2+,
    (���˷�ʽ)
    //                =110 ͨ��1+,        =111 ͨ��3+,
    (���˷�ʽ)
*/
    chanel |=0x08;        //������ʼλ
    for(i=0; i<4; i++)
    {
        if( (chanel &0x08)!=0)
        {
            SET_ADC083X_DI;
        }
        else
        {
            CLR_ADC083X_DI;
        }
        SET_ADC083X_CLK;
        CLR_ADC083X_CLK;
        chanel <<=1;
    }

#elif (TYPE_VAL==ADC0832)
		/*
    //chanel_.1    .0        =00 ͨ��0+_ͨ��1-, =01 ͨ��0-_ͨ��
1+,    (˫�˷�ʽ)
    //    SGL/DIF ODD/SIGN    =10 ͨ��0+,       =11 ͨ��1+,    
    (���˷�ʽ)
 */   
    chanel |=0x04;        //������ʼλ
    for(i=0; i<3; i++)
    {
        if( (chanel &0x04)!=0)
        {
            SET_ADC083X_DI;
        }
        else
        {
            CLR_ADC083X_DI;
        }
        SET_ADC083X_CLK;
        CLR_ADC083X_CLK;
        chanel <<=1;
    }

#else    //ȱʡʱΪADC0831
    
    SET_ADC083X_CLK;
    CLR_ADC083X_CLK;
    
#endif

    SET_ADC083X_CLK;    //���ݽ���ǰ��ת��λ
    CLR_ADC083X_CLK;

    for(ad_val=0, i=0; i<8; i++)
    {
        ad_val <<=1;
        SET_ADC083X_CLK;
        ad_val +=(JUDGE_ADC083X_DO ==1? 1:0);
        CLR_ADC083X_CLK;
    }    
    //�Է�ADC0831���ͺŶ���,��������û��ʹ�ã�

    SET_ADC083X_CS;
    return(ad_val);
}

//=============================================================================
//End Of File 

 
 
 