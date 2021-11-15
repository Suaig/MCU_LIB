#include <reg51.h>

#include "PID.h"
#include "ADC083X.h"
#include "math.h"
#include "LCD1602.h"
#include "stdio.h"

uint32_t millis();
float NTC_Temp(void);
void KeyScan();
uint32_t tick = 0;


idata PID_Class adout;


uint8_t PWM = 0;
double input,output,set = 40;
void main()
{
	uint8_t disbuff[16];
	uint8_t volatile num = 0;
	
	LCD_Init();
	
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
	ET0 = 1;
	
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0x06;		//���ö�ʱ��ֵ
	TH1 = 0x06;		//���ö�ʱ����ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	
	ET1 = 1;
	EA = 1;
	
	/********************************
	���ȣ���ôȷ���������ڣ������ϵͳ��������Ƶ�������������Ƶ�60%-80%֮���ʱ��(������ϵͳ��ͬ������)
	eg:������:������:�����һ�����Ʊ�����X,�������޳���ʱ�䣬�¶�ͣ����Y����ô�����ȡ�¶�������0.6Y-0.8Y�����ʱ�䣬
	������Щϵͳ�����Գ̶Ⱥܸ����ݺ����ı仯�����ʱ��Ҫ�ﵽ��õĿ���Ч�����һ����Ӽ����ʱ����
	
	ȷ��Kp,Ki��Kd��һ���ò���Kd�Ϳ����кܺõĿ���Ч����Kd��һ�������д��ͺ��ϵͳ����������¶ȣ�
	Kd�������¶Ȼ�û�е�������ֵ��ʱ��ͼ��ٿ������
	
	���ȣ���Ki��Kd���ó�0�����ϼӴ�Kpֱ�������񵴣���Ϊ����㣬
	Ȼ��:Ki�����ӣ��ӵ���ʼ�񵴣�ȡ��80%-90%
	
	���ϵͳ���������ͺ�����������Kd��ֵ��ʹ�õ�һ�γ����͵ڶ��εķ��4��1���������
	
	PID������ɢ��ʽ:OUT = kp * error + (ki * T)/Ti * ��error + kd *Td/T * ��error

	T:PID����������ڣ�Ti:����ʱ�� Td:΢��ʱ�� error:����������ֵ�Ĳ�    ��error:�ۻ���error 

	��error:����error�Ĳ�	
	
	*********************************/
	adc083x_init();
	LCD_Clear();
	new_PID(&adout,&input,&output,&set,1.4,0.1,0,P_ON_E,DIRECT);//����ģʽ�������
	PID_Initialize(&adout);//��ʼ��
	
	PID_SetMode(&adout,AUTOMATIC);//�Զ�����ģʽ
	PID_SetOutputLimits(&adout,0,255);
	PID_SetSampleTime(&adout,5000);//����PID��������Ϊ5000ms
	LCD_PutString(0,0,"Set:");
	LCD_PutString(0,1,"Temp:");
	while(1)
	{
		input = NTC_Temp();//��ȡ�¶�
		sprintf(disbuff,"Temp:%2.1f'C",input);
		LCD_PutString(0,1,disbuff);//��ʾ��ǰ�¶�
		sprintf(disbuff,"Set:%2.1f'C ",set);
		LCD_PutString(0,0,disbuff);//��ʾ����ֵ
		if(PID_Compute(&adout) == true)//�����β�������һ��,�¶ȱ仯��������������������ڸ����Լ������豸���ж�
		{
			
			PWM = (uint8_t)output;
		}
		KeyScan();
	}
}
void KeyScan()
{
	static uint8_t lastkey = (0x03<<4);
	uint8_t key = P1&(0x03<<4);
	if(key != lastkey && lastkey == (0x03<<4))//ɨ�赽�½���
	{
		switch(key)
		{
			case 0x00<<4://��������ͬʱ����,������
			{
				
			}
			break;
			case 0x01<<4:
			{
				
				set = (((int)set)-1);
			}
			break;
			case 0x02<<4:
			{
				
				set = (((int)set)+1);
			}
			break;
		}
	}
	lastkey = key;
}
uint32_t millis()
{
	return tick;
}
float NTC_Temp(void)
{
	const float Rp=10000.0; //10K
	const float T2 = (273.15+25.0);//T2
	const float Bx = 3950.0;//B NTC��Bֵ
	const float Ka = 273.15;
	float Rt;
	float temp;
	Rt = (float)adc083x_do_one_change(0x02);//�ɼ���ѹ
	Rt = Rp*(255-Rt)/Rt;//����NTC����
	//like this R=5000, T2=273.15+25,B=3470, RT=5000*EXP(3470*(1/T1-1/(273.15+25)),  
	temp = Rt/Rp;
	temp = log(temp);//ln(Rt/Rp)
	temp/=Bx;//ln(Rt/Rp)/B
	temp+=(1/T2);
	temp = 1/(temp);
	temp-=Ka;
	return temp;
} 
void Timer1_IRQ() interrupt 3 //����PWM���
{
	static uint8_t i=0;
	if(PWM >= i)
	{
		P3 |= 0x01;//��
	}
	else
	{
		P3 &= ~(0x01);//��
	}
	i++;
}
void Timer0_IRQ() interrupt 1
{
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	
	tick++;

}