#include "DHT11.h"

void dht11_Init(DHT11_t *dht,dht11_msg_cb dht_cb)
{
	dht->gpio_and_delay_cb = dht_cb;
	dht->gpio_and_delay_cb(dht,DHT11_MSG_SDA_HIGH);
	dht->gpio_and_delay_cb(dht,DHT11_MSG_2S_DELAY);//��֤�ϵ�2SԽ��dht11���ȶ�״̬
}
uint8_t dht11_Read(DHT11_t *dht)
{
	uint8_t i,j,sum;
	dht->DHT11_RXD_Buff[0] = dht->DHT11_RXD_Buff[1] = dht->DHT11_RXD_Buff[2] = dht->DHT11_RXD_Buff[3] = dht->DHT11_RXD_Buff[4] = 0;
	dht->gpio_and_delay_cb(dht,DHT11_MSG_SDA_HIGH);//��������
	dht->gpio_and_delay_cb(dht,DHT11_MSG_1MS_DELAY);//��ʱ1ms
	dht->gpio_and_delay_cb(dht,DHT11_MSG_SDA_LOW);//����
	
	dht->gpio_and_delay_cb(dht,DHT11_MSG_18MS_DELAY);//��ʱ18ms

	
	dht->gpio_and_delay_cb(dht,DHT11_MSG_SDA_HIGH);//Ȼ������
	dht->gpio_and_delay_cb(dht,DHT11_MSG_30US_DELAY);//�ȴ�30us
		//����һ����ʼ�źţ��ȴ��ӻ�����
	if(dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA) == 0)//�������ǵ͵�ƽ���ӻ���Ӧ�ˣ���ô�ȴ����ߺ�׼����������
	{
		while(!dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA));//�ȴ��͵�ƽ����
	}
	else
	{
		return 1;//ֱ�ӷ��أ���������ȴ��ߵ�ƽ������ѭ��
	}
	while(dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA));//�ȴ�80us�ĸߵ�ƽ������Ȼ��ʼ����
	
	for(j=0;j<5;j++)
	{
		for(i=0;i<8;i++)
		{
			while(!dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA));//�ȴ�50us���ҵĵ͵�ƽ����
			dht->DHT11_RXD_Buff[j] <<=1;
			dht->gpio_and_delay_cb(dht,DHT11_MSG_30US_DELAY);//��ʱ1ms
			if(dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA))
			{
				dht->DHT11_RXD_Buff[j] |= 0x01;
				while(dht->gpio_and_delay_cb(dht,DHT11_MSG_READ_SDA));//�ȴ��ߵ�ƽ����
			}
		}
	}
	
	sum = dht->DHT11_RXD_Buff[0] + dht->DHT11_RXD_Buff[1] + dht->DHT11_RXD_Buff[2] + dht->DHT11_RXD_Buff[3];
	
	if(sum != dht->DHT11_RXD_Buff[4] || sum == 0) return 1;//���У���
	
	return 0;
}
uint8_t DHT11_Fget(DHT11_t *dht,float *Humi,float *Temp)
{
	
	uint16_t t = 0x0000;
	uint8_t sum = 0;
	sum = dht->DHT11_RXD_Buff[0] + dht->DHT11_RXD_Buff[1] + dht->DHT11_RXD_Buff[2] + dht->DHT11_RXD_Buff[3];
	
	if(sum != dht->DHT11_RXD_Buff[4] || sum == 0) return 1;//���У���
	t |= dht->DHT11_RXD_Buff[0];
	
	*Humi = (float)t;
	
	t = 0x0000;
	
	t = dht->DHT11_RXD_Buff[2];

	*Temp = (float)t;
	return 0;
}
uint8_t DHT11_Iget(DHT11_t *dht,int16_t *Humi,int16_t *Temp)
{
	
	int16_t t = 0x0000;
	uint8_t sum = 0;
	sum = dht->DHT11_RXD_Buff[0] + dht->DHT11_RXD_Buff[1] + dht->DHT11_RXD_Buff[2] + dht->DHT11_RXD_Buff[3];
	
	if(sum != dht->DHT11_RXD_Buff[4] || sum == 0) return 1;//���У���
	
	t |= dht->DHT11_RXD_Buff[0];
	//t <<= 8;
	//t |= dht->dht11_RXD_Buff[1];
	
	*Humi = (int16_t)t;
	
	t = 0x0000;
	
	t = dht->DHT11_RXD_Buff[2];


	*Temp = (int16_t)t;
	return 0;
}