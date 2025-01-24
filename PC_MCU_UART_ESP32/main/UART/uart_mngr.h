#ifndef UART_MNGR_H
#define UART_MNGR_H

#include "uart_hal.h"

void write_uart(void);
void read_uart(void);
void print_uart(void);
extern void init_uart_task(void);
extern volatile size_t current_byte_index; // Tracks the current byte being sent
extern volatile size_t bytes_sent_in_1s;   // Counts the bytes sent in 1 second
extern bool transmission_complete;
#endif // UART_MNGR_H