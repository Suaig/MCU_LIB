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
      return 1; //超时间，没有在指定时间内接收到信号量
    }
    else
    {
    WaitTick(1);//返回255 任务正在运行，信号量正在等待
    }
  }
  _EE
	(*s) == 0 ? (*s) = 1 : (*s);
  return 0;//返回0 成功在指定时间内接收到信号量
}
#endif
