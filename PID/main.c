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
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;
	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0x06;		//设置定时初值
	TH1 = 0x06;		//设置定时重载值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	
	ET1 = 1;
	EA = 1;
	
	/********************************
	首先，怎么确定计算周期，大概是系统从输出控制到上升到输出控制的60%-80%之间的时间(可以视系统不同而调节)
	eg:举例子:加热器:我输出一个控制比如是X,经过无限长的时间，温度停留在Y，那么大概是取温度上升到0.6Y-0.8Y的这个时间，
	由于有些系统非线性程度很高是幂函数的变化，这个时候，要达到最好的控制效果，我会增加计算的时间间隔
	
	确定Kp,Ki，Kd，一般用不到Kd就可以有很好的控制效果，Kd我一般用于有大滞后的系统，例如控制温度，
	Kd可以在温度还没有到达设置值的时候就减少控制输出
	
	首先，把Ki，Kd设置成0，不断加大Kp直到产生振荡，作为启振点，
	然后:Ki慢慢加，加到开始振荡，取其80%-90%
	
	如果系统控制严重滞后，慢慢的增加Kd的值，使得第一次超调和第二次的峰比4比1是最理想的
	
	PID完整离散公式:OUT = kp * error + (ki * T)/Ti * ∑error + kd *Td/T * △error

	T:PID计算采样周期，Ti:积分时间 Td:微分时间 error:采样和期望值的差    ∑error:累积的error 

	△error:两次error的差	
	
	*********************************/
	adc083x_init();
	LCD_Clear();
	new_PID(&adout,&input,&output,&set,1.4,0.1,0,P_ON_E,DIRECT);//正常模式，正相关
	PID_Initialize(&adout);//初始化
	
	PID_SetMode(&adout,AUTOMATIC);//自动计算模式
	PID_SetOutputLimits(&adout,0,255);
	PID_SetSampleTime(&adout,5000);//设置PID计算周期为5000ms
	LCD_PutString(0,0,"Set:");
	LCD_PutString(0,1,"Temp:");
	while(1)
	{
		input = NTC_Temp();//获取温度
		sprintf(disbuff,"Temp:%2.1f'C",input);
		LCD_PutString(0,1,disbuff);//显示当前温度
		sprintf(disbuff,"Set:%2.1f'C ",set);
		LCD_PutString(0,0,disbuff);//显示设置值
		if(PID_Compute(&adout) == true)//大概五次采样计算一次,温度变化很慢，这个采样计算周期根据自己加热设备来判断
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
	if(key != lastkey && lastkey == (0x03<<4))//扫描到下降沿
	{
		switch(key)
		{
			case 0x00<<4://两个按键同时按下,不操作
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
	const float Bx = 3950.0;//B NTC的B值
	const float Ka = 273.15;
	float Rt;
	float temp;
	Rt = (float)adc083x_do_one_change(0x02);//采集电压
	Rt = Rp*(255-Rt)/Rt;//计算NTC电阻
	//like this R=5000, T2=273.15+25,B=3470, RT=5000*EXP(3470*(1/T1-1/(273.15+25)),  
	temp = Rt/Rp;
	temp = log(temp);//ln(Rt/Rp)
	temp/=Bx;//ln(Rt/Rp)/B
	temp+=(1/T2);
	temp = 1/(temp);
	temp-=Ka;
	return temp;
} 
void Timer1_IRQ() interrupt 3 //用于PWM输出
{
	static uint8_t i=0;
	if(PWM >= i)
	{
		P3 |= 0x01;//高
	}
	else
	{
		P3 &= ~(0x01);//低
	}
	i++;
}
void Timer0_IRQ() interrupt 1
{
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	tick++;

}