#ifndef UART_CONF_H
#define UART_CONF_H

#include "driver/uart.h"

#define UART_1_TX 6
#define UART_1_RX 5
#define UART_1_RTS UART_PIN_NO_CHANGE
#define UART_1_CTS UART_PIN_NO_CHANGE

#define UART_1_RX_BUFF 1024
#define UART_1_TX_BUFF 1024

#define UART_TX_DATA_LEN 12
#define UART_RX_DATA_LEN 21

#define RX_PAYLOAD_LEN 20
#define TX_PAYLOAD_LEN 8

extern uart_config_t uart_config;

extern const uart_port_t uart_num;

#endif // UART_CONF_H