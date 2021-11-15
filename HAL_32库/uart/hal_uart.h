#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include "ringBuffer.h"
#include "main.h"
#include "usart.h"

HAL_StatusTypeDef hal_uart1_begin(void); //串口1缓冲区开启
HAL_StatusTypeDef hal_uart2_begin(void); //串口1缓冲区开启

size_t hal_uart1_can_read(void);
size_t hal_uart2_can_read(void);

int32_t hal_uart1_read(uint8_t *buff, size_t len);
int32_t hal_uart2_read(uint8_t *buff, size_t len);

int32_t hal_uart1_putdata(uint8_t *buf, uint32_t len);
int32_t hal_uart2_putdata(uint8_t *buf, uint32_t len);

int32_t hal_uart1_getdata(uint8_t *buf, uint32_t len);
int32_t hal_uart2_getdata(uint8_t *buf, uint32_t len);

int32_t hal_uart1_write(uint8_t *buf, uint32_t len);
int32_t hal_uart2_write(uint8_t *buf, uint32_t len);
#endif
