#include "PID.h"
//�½�һ��PID���󣬺���������Ӧ���������
//mpid:PID����
//Input:�ɼ���
//Output:���������
//Setpoint:��������ֵ
//Kp:��������ϵ��
//Ki:���ֻ���ϵ��
//Kd:΢�ֻ���ϵ��
//Pon:����ģʽ
//ControllerDirection:���Ʒ���
//ʵ��д�����ʱ���PID����ʵ���ǵ�Kp��Ki��Kd��sampletime�ĸ�����
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
void new_PID(PID_Class *mpid,PID_type* Input,PID_type* Output,PID_type* Setpoint,PID_type Kp,PID_type Ki,PID_type Kd,bool POn, bool ControllerDirection)
{
    mpid->myOutput = Output;//myOutput����
    mpid->myInput = Input;	//myInput����
    mpid->mySetpoint = Setpoint;//mySetpoint����
    mpid->inAuto = false;//inAuto���� Ĭ��Ϊ�ֶ�ģʽ

    PID_SetOutputLimits(mpid,0,255);				//Ĭ������޷���255�Ǹ���arduino��Ƭ�����õ�

    mpid->SampleTime = 200;							//Ĭ�ϼ�����0.2s��200ms����������Ҫ��PID�ṩ1ms�ļ���������200�Ŷ�Ӧ200ms��Ҳ����ʵ��PIDmillis()����

    PID_SetControllerDirection(mpid,ControllerDirection);//���ÿ��Ʒ���
																													//DIRECT  0  : PID������� ����������
																													//REVERSE  1 : PID������ӣ�����������  �ο��յ����䣬����������ӣ��յ�������ǿ��Խ��
    PID_SetTunings(mpid,Kp, Ki, Kd, POn);	//����PID����ʽ����ϵ���Լ�����ģʽ�ǳ�����������ģʽ

    mpid->lastTime = PIDmillis()-(mpid->SampleTime);	//��ʼ��lastTime��ʹ��һ�ο���ֱ�ӿ�ʼPID����
}
//����PID����ʽ����ϵ���Լ�����ģʽ�ǳ�����������ģʽ
//mpid:PID����
//Kp:��������ϵ��
//Ki:���ֻ���ϵ��
//Kd:΢�ֻ���ϵ��
//POn:����ģʽ 	P_ON_M(0)	���Ƴ���(������ֳ��������߳���С��������)
//							P_ON_E(1)	����ģʽ(�г�������������)
void PID_SetTunings(PID_Class *mpid,PID_type Kp, PID_type Ki, PID_type Kd, bool POn)
{
		PID_type SampleTimeInSec = 0;
   if (Kp<0 || Ki<0 || Kd<0) return;

   //mpid->pOn = POn;
   mpid->pOnE = POn;

   mpid->dispKp = Kp; mpid->dispKi = Ki; mpid->dispKd = Kd;

   SampleTimeInSec = ((PID_type)mpid->SampleTime)/1000;
   mpid->kp = Kp;
   mpid->ki = Ki * SampleTimeInSec;
   mpid->kd = Kd / SampleTimeInSec;

  if(mpid->controllerDirection ==REVERSE)
   {
      mpid->kp = (0 - mpid->kp);
      mpid->ki = (0 - mpid->ki);
      mpid->kd = (0 - mpid->kd);
   }
}
//����PID��������
//mpid:PID����
//NewSampleTime:��������Ϊ���ٸ�ʱ��Ƭ��PIDmillis()ֵ1��Ӧ�೤ʱ�䣬һ��ȡ1ms��
void PID_SetSampleTime(PID_Class *mpid,Timetick NewSampleTime)
{
	PID_type SampleTimeInSec = 0;
   if (NewSampleTime > 0)
   {
      PID_type ratio  = (PID_type)NewSampleTime
                      / (PID_type)mpid->SampleTime;
      mpid->ki *= ratio;
      mpid->kd /= ratio;
      mpid->SampleTime = (Timetick)NewSampleTime;
		 
	 

   SampleTimeInSec = ((PID_type)mpid->SampleTime)/1000;
   mpid->kp = mpid->dispKp;
   mpid->ki = mpid->dispKi * SampleTimeInSec;
   mpid->kd = mpid->dispKd / SampleTimeInSec;//����PIDϵ��
		 
	 mpid->lastTime = PIDmillis()-(mpid->SampleTime);
   }
}
//����PID����޷���С
//mpid:PID����
//Min:�����Сֵ�޷�
//Max:������ֵ�޷�
void PID_SetOutputLimits(PID_Class *mpid,PID_type Min, PID_type Max)
{
   if(Min >= Max) return;
   mpid->outMin = Min;
   mpid->outMax = Max;

   if(mpid->inAuto)
   {
	   if(*(mpid->myOutput) > (mpid->outMax)) *(mpid->myOutput) = (mpid->outMax);
	   else if(*(mpid->myOutput) < (mpid->outMin)) *(mpid->myOutput) = (mpid->outMin);

	   if((mpid->outputSum) > mpid->outMax) (mpid->outputSum)= mpid->outMax;
	   else if((mpid->outputSum) < mpid->outMin) mpid->outputSum= mpid->outMin;
   }
}
//����PIDģʽ���Զ����ֶ���
//mpid:PID����
//Mode: AUTOMATIC(1)��ʱ���Զ�����
//			MANUAL	(0)	�ֶ�
void PID_SetMode(PID_Class *mpid,bool Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto && !(mpid->inAuto))
    {  
        PID_Initialize(mpid);
    }
    mpid->inAuto = newAuto;
}
//PID�����ʼ��
void PID_Initialize(PID_Class *mpid)
{
   mpid->outputSum = *(mpid->myOutput);
   mpid->lastInput = *(mpid->myInput);
   if(mpid->outputSum > mpid->outMax) mpid->outputSum = mpid->outMax;
   else if(mpid->outputSum < mpid->outMin) mpid->outputSum = mpid->outMin;
}
//����PID���Ʒ���
//Direction:	DIRECT  0  : PID������� ����������
//						REVERSE  1 : PID������ӣ�����������  �ο��յ����䣬����������ӣ��յ�������ǿ��Խ��
void PID_SetControllerDirection(PID_Class *mpid,bool Direction)
{
   if(mpid->inAuto && Direction !=mpid->controllerDirection)
   {
	    mpid->kp = (0 - mpid->kp);
      mpid->ki = (0 - mpid->ki);
      mpid->kd = (0 - mpid->kd);
   }
   mpid->controllerDirection = Direction;
}

//PID���㣬��while�в��ϵ���
bool PID_Compute(PID_Class *mpid)
{
	 PID_type output = 0;
	Timetick now;					//�洢������к�����ʱ���
	Timetick timeChange;	//�洢�ϴ�ִ����PID����ν��뺯����ʱ���
   if(!(mpid->inAuto))	//�ֶ�����ģʽ�¸ú���ʧЧ��ֱ�ӷ���false
	 {
		 return false;
	 }
	 now = PIDmillis();		//��ȡʱ�����
   timeChange = (now - mpid->lastTime);	//�õ�ʱ���
   if(timeChange>=(mpid->SampleTime))	//���ʱ�����ڵ��ڼ���������ʼPID����
   {
      /*Compute all the working error variables*/
      PID_type input = *(mpid->myInput);	//�ɼ���������
      PID_type error = *(mpid->mySetpoint) - input;	//�ɼ�ֵ������ֵ��ƫ��
      PID_type dInput = (input - mpid->lastInput);	//��βɼ�ֵ���ϴβɼ�ֵ�Ĳ����error
      mpid->outputSum+= (mpid->ki * error);	//���ֻ��� ���ڻ��ֻ�������ʷ�йأ���outputSum����ʷֵӰ��

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if(!(mpid->pOnE)) (mpid->outputSum)-= (mpid->kp) * dInput;	//P_ON_Mģʽ�����Ƴ������� ���ֻ��ڼ��볬������

      if((mpid->outputSum) > (mpid->outMax)) (mpid->outputSum)= (mpid->outMax);	//���Ǵ����޷����ܵ�PID����ֹ���ڹ��󣩣����������ֵʱ��ȡ�����ֵ
      else if((mpid->outputSum) < (mpid->outMin)) (mpid->outputSum)= (mpid->outMin);	//������С��ֵʱ��ȡ��С��ֵ

      /*Add Proportional on Error, if P_ON_E is specified*/
      if(mpid->pOnE) output = mpid->kp * error;										//P_ON_Eģʽ(����ģʽ)�£�outputֱ�Ӹ�ֵ�������ڲ���
      else output = 0;																						//P_ON_Mģʽ(���Ƴ���)�£������ڻ��ֻ����м����˱������ڿ��ƣ�����outputֱ�Ӹ�ֵ0

      /*Compute Rest of PID Output*/ //����PIDʽ��ʣ���kd��΢�ֻ��ڣ� 
      output += mpid->outputSum - mpid->kd * dInput;	//P_ON_Eģʽ�£�output��ִ���������֮ǰ������kp���������ڣ����֣�outputSum�����˻��ֲ��֣�����ʷֵ�йأ�
																											//P_ON_Mģʽ�£�outputΪ0��outputSum���ܱ�������Ӱ��Ļ��ֲ��֣�Ҳ���ǰ���������
	    if(output > mpid->outMax) output = mpid->outMax;	//���ֵ�޷�
      else if(output < mpid->outMin) output = mpid->outMin;	//��Сֵ�޷�
	    *(mpid->myOutput) = output;	//�洢output������

      /*Remember some variables for next time*/
      mpid->lastInput = input;	//����˴βɼ�ֵ���Ա��´����error
      mpid->lastTime = now;	//����˴μ�����ϵ�ʱ��㣬�Ա��´��ж��Ƿ��˼�������
	    return true;		//������ϣ�����true
   }
   else return false;	//δ���������ڣ�ֱ�ӷ���false
}