#include "OS_thead.h"

#if FSEMX > 0u
SEM WaitSemX(SEM *s,uint16_t t)
{
  _SS
  while((*s) != 0)
  {
    (*s)++;
    if((*s) >= t)
    {
      (*s) = 1;
      return 1; //��ʱ�䣬û����ָ��ʱ���ڽ��յ��ź���
    }
    else
    {
    WaitTick(1);//����255 �����������У��ź������ڵȴ�
    }
  }
  _EE
	(*s) == 0 ? (*s) = 1 : (*s);
  return 0;//����0 �ɹ���ָ��ʱ���ڽ��յ��ź���
}
#endif
