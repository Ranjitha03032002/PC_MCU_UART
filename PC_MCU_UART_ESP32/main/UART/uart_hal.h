#ifndef UART_HAL_H
#define UART_HAL_H

#include "uart_conf.h"

void uart_1_init(void);

void Uart_HAL_SendData(uint32_t instance, uint8_t *txPayload, uint8_t Payload_Size);
void Uart_HAL_ReceiveData(uint32_t instance, uint8_t *RxPayload, uint8_t Payload_Size);

#endif // UART_HAL_H