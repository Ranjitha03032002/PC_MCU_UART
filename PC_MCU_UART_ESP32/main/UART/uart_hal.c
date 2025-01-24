// uart_hal.c

#include "uart_hal.h"
#include "esp_intr_alloc.h"
#include "driver/uart.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_intr_alloc.h"
#include "eeprom_hal.h"

static intr_handle_t handle_console;
volatile uint32_t offset = 0; // EEPROM offset

static void IRAM_ATTR uart_intr_handle(void *arg)
{
    uint16_t rx_fifo_len, status;
    uint16_t i;

    printf("\n********** UART Interript *********8\n");
    //   status = UART0.int_st.val; // read UART interrupt Status
    //   rx_fifo_len = UART0.status.rxfifo_cnt; // read number of bytes in UART buffer

    //   while(rx_fifo_len){
    //    rxbuf[i++] = UART0.fifo.rw_byte; // read all bytes
    //    rx_fifo_len--;
}

void uart_1_init(void)
{

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_1_TX, UART_1_RX, UART_1_RTS, UART_1_CTS));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_1_RX_BUFF, UART_1_TX_BUFF, 0, NULL, 0));

    // release the pre registered UART handler/subroutine
    // ESP_ERROR_CHECK(uart_isr_free(uart_num));

    // register new UART subroutine
    // ESP_ERROR_CHECK(uart_isr_register(uart_num, uart_intr_handle, NULL, ESP_INTR_FLAG_IRAM, &handle_console));

    // enable RX interrupt
    // ESP_ERROR_CHECK(uart_enable_rx_intr(uart_num));

    if (uart_is_driver_installed(uart_num))
        printf("\nUart Installed Properly\n");
}

void Uart_HAL_SendData(uint32_t instance, uint8_t *txPayload, uint8_t Payload_Size)
{
    int bytes_written = uart_write_bytes(instance, txPayload, Payload_Size);

    if (bytes_written < 0)
    {
        printf("UART write error\n");
    }
}

void Uart_HAL_ReceiveData(uint32_t instance, uint8_t *RxPayload, uint8_t Payload_Size)
{
    // Read the data
    int bytes_read = uart_read_bytes(instance, RxPayload, Payload_Size, 40);
    if (bytes_read >= 1)
    {
        printf("%c", *RxPayload);
        // esp_err_t eeprom_ret = write_TripID_byte_eeprom(RxPayload, offset);
        // if (eeprom_ret == ESP_OK)
        {
            // printf("Stored byte at offset %ld\n", offset);
        }
        // else
        {
            // printf("Failed to store byte at offset %ld. Error: %d\n", offset, eeprom_ret);
        }
        offset++;
        // printf("************************ uart receive happening  ***************************************\n");
    }
    else
    {
        // No bytes were received
        // UartRecCounter++;
        // printf("************************ uart receive not happening  ***************************************\n");
    }
}

// #define CHUNK_SIZE 16
// uint8_t chunk_buffer[CHUNK_SIZE];
// size_t chunk_index = 0;
// size_t chunk_offset = 0;

// void Uart_HAL_ReceiveData(uint32_t instance, uint8_t *RxPayload, uint8_t Payload_Size)
// {
//     int bytes_read = uart_read_bytes(instance, RxPayload, Payload_Size, 40);
//     if (bytes_read >= 1)
//     {
//         printf("%c", *RxPayload);

//         // Add to chunk buffer
//         chunk_buffer[chunk_index++] = *RxPayload;

//         // When buffer is full, store it in EEPROM
//         if (chunk_index >= CHUNK_SIZE)
//         {
//             esp_err_t eeprom_ret = write_TripID_chunk_eeprom(chunk_buffer, CHUNK_SIZE, chunk_offset++);
//             if (eeprom_ret == ESP_OK)
//             {
//                 printf("Stored chunk at offset %d\n", chunk_offset);
//             }
//             else
//             {
//                 printf("Failed to store chunk at offset %d. Error: %d\n", chunk_offset, eeprom_ret);
//             }
//             chunk_index = 0; // Reset buffer index
//         }
//     }
// }
