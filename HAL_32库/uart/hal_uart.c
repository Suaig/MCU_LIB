#include "hal_uart.h"


rb_t uart1_rb_rx;
rb_t uart1_rb_tx;

rb_t uart2_rb_rx;
rb_t uart2_rb_tx;


uint8_t uart1_rx_rb[256];
uint8_t uart2_rx_rb[256];

uint8_t uart1_tx_rb[256];
uint8_t uart2_tx_rb[256];

uint8_t uart1_rx_buff,uart2_rx_buff;
uint8_t uart1_tx_buff,uart2_tx_buff;


HAL_StatusTypeDef hal_uart1_begin(void)
{

    uart1_rb_rx.rbCapacity = 256;
    uart1_rb_rx.rbBuff = uart1_rx_rb; //�������ܻ�����
    if(0 == rbCreate(&uart1_rb_rx))
    {

        HAL_UART_Receive_IT(&huart1,&uart1_rx_buff,1);
        //ret =  HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }

    uart1_rb_tx.rbCapacity = 256;
    uart1_rb_tx.rbBuff = uart1_tx_rb;
    if(0 == rbCreate(&uart1_rb_tx))
    {
        //ret = HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}



HAL_StatusTypeDef hal_uart2_begin(void)
{

    uart2_rb_rx.rbCapacity = 256;
    uart2_rb_rx.rbBuff = uart2_rx_rb; //�������ܻ�����
    if(0 == rbCreate(&uart2_rb_rx))
    {

        HAL_UART_Receive_IT(&huart2,&uart2_rx_buff,1);
        //ret =  HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }

    uart2_rb_tx.rbCapacity = 256;
    uart2_rb_tx.rbBuff = uart2_tx_rb;
    if(0 == rbCreate(&uart2_rb_tx))
    {
        //ret = HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}
size_t hal_uart1_can_read(void) //�������ж������ݿɶ�
{
    return rbCanRead(&uart1_rb_rx);
}
size_t hal_uart2_can_read(void) //�������ж������ݿɶ�
{
    return rbCanRead(&uart2_rb_rx);
}
int32_t hal_uart1_read(uint8_t *buff, size_t len) //����N��
{
    int32_t count = 0;
    if(NULL == buff)
    {
        return -1;
    }
	 
	 count = rbRead((void *)&uart1_rb_rx,buff,len);
	 
	 
    if(count != len)
    {

        return -1;
    }
    return count;
}

int32_t hal_uart2_read(uint8_t *buff, size_t len) //����N��
{
    int32_t count = 0;
    if(NULL == buff)
    {
        return -1;
    }
	 
	 count = rbRead((void *)&uart2_rb_rx,buff,len);
	 
	 
    if(count != len)
    {

        return -1;
    }
    return count;
}

int32_t hal_uart1_putdata(uint8_t *buf, uint32_t len)//���ڽ����ж������ڽ����ܵ�������ѹ���жϡ�
{
    int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }

    count = rbWrite(&uart1_rb_rx, buf, len);
    if(count != len)
    {

        return -1;
    }

    return count;
}
int32_t hal_uart2_putdata(uint8_t *buf, uint32_t len)//���ڽ����ж������ڽ����ܵ�������ѹ���жϡ�
{
    int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }

    count = rbWrite(&uart2_rb_rx, buf, len);
    if(count != len)
    {

        return -1;
    }

    return count;
}
//�ӻ�������ȡn��
int32_t hal_uart1_getdata(uint8_t *buf, uint32_t len)//���ڷ����ж��������ٴ��������ݻ��߽�������
{
    int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }
	 count = rbCanRead(&uart1_rb_tx);
	 if(len > count)
	 {
		 return -1;
	 }
    count = rbRead(&uart1_rb_tx, buf, len);
    if(count != len)//��ȡ����
    {

        return -1;
    }
    return count;
}
int32_t hal_uart2_getdata(uint8_t *buf, uint32_t len)//���ڷ����ж��������ٴ��������ݻ��߽�������
{
    int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }
	 count = rbCanRead(&uart2_rb_tx);
	 if(len > count)
	 {
		 return -1;
	 }
    count = rbRead(&uart2_rb_tx, buf, len);
    if(count != len)
    {

        return -1;
    }
    return count;
}
int32_t hal_uart1_write(uint8_t *buf, uint32_t len)//д�뷢�ͻ�����׼������
{
	 int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }
	 count = rbCanWrite(&uart1_rb_tx);//�������ж��ٿ�д
	 if(count < len) //������λ�ò�������Ҫ�ȴ����ͣ����߷���һ��
	 {
		 return -1;
	 }
	 count = rbWrite(&uart1_rb_tx, buf, len);
	 
	 if(huart1.gState == HAL_UART_STATE_READY)
	 {
		 
		 hal_uart1_getdata(&uart1_tx_buff,1);
		 HAL_UART_Transmit_IT(&huart1,&uart1_tx_buff,1);//�����жϷ���
	 }
	 return count;
}
int32_t hal_uart2_write(uint8_t *buf, uint32_t len)//д�뷢�ͻ�����׼������
{
	 int32_t count = 0;

    if(NULL == buf)
    {
        return -1;
    }
	 count = rbCanWrite(&uart2_rb_tx);//�������ж��ٿ�д
	 if(count < len) //������λ�ò�������Ҫ�ȴ����ͣ����߷���һ��
	 {
		 return -1;
	 }
	 count = rbWrite(&uart2_rb_tx, buf, len);
	 
	 if(huart2.gState == HAL_UART_STATE_READY)
	 {
		 
		 hal_uart2_getdata(&uart2_tx_buff,1);
		 HAL_UART_Transmit_IT(&huart2,&uart2_tx_buff,1);//�����жϷ���
	 }
	 return count;
}
//�жϻص�����
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1) //����˽��յ�������ȫ��������ͨ��huart2���ͳ�ȥ
	{
		hal_uart1_putdata(&uart1_rx_buff,1);
		HAL_UART_Receive_IT(&huart1,&uart1_rx_buff,1);
	}
	if(huart->Instance == USART2)
	{
		hal_uart2_putdata(&uart2_rx_buff,1);
		HAL_UART_Receive_IT(&huart2,&uart2_rx_buff,1);

	}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1) //����˽��յ�������ȫ��������ͨ��huart2���ͳ�ȥ
	{
		if(hal_uart1_getdata(&uart1_tx_buff,1) != -1) //��������
		{
			HAL_UART_Transmit_IT(&huart1,&uart1_tx_buff,1);
		}
	}
	if(huart->Instance == USART2)
	{
		if(hal_uart2_getdata(&uart2_tx_buff,1) != -1)
		{
			HAL_UART_Transmit_IT(&huart2,&uart2_tx_buff,1);
		}

	}
}

