#include "driver/uart.h"
#include <stdint.h>
#include "string.h"
#include "stdbool.h"

#define UART_1_TX 6
#define UART_1_RX 5
#define UART_1_RTS UART_PIN_NO_CHANGE
#define UART_1_CTS UART_PIN_NO_CHANGE

#define UART_1_RX_BUFF 1024
#define UART_1_TX_BUFF 1024
#define TERMINATION_SEQUENCE "iii"   // Define the termination sequence
#define TERMINATION_LENGTH 3         // Length of the termination sequence
#define MAX_RECEIVE_BUFFER_SIZE 1024 // Adjust as needed

extern uart_config_t uart_config;

extern const uart_port_t uart_num;

extern volatile size_t current_byte_index; // Tracks the current byte being sent
extern volatile size_t bytes_sent_in_1s;   // Counts the bytes sent in 1 second
extern volatile bool transmission_complete;
extern volatile bool reception_complete;

void uart_1_init(void);
void Uart_HAL_SendData(uint32_t instance, uint8_t *txPayload, uint8_t Payload_Size);
void Uart_HAL_ReceiveData(uint32_t instance, uint8_t *RxPayload, uint8_t Payload_Size);

void write_uart(void);
void read_uart(void);
