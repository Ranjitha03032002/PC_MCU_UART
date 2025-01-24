// uart_mngr.c

#include "uart_mngr.h"
#include "string.h"
#include "eeprom_hal.h"
char uart_payload[21] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile size_t current_byte_index = 0; // Tracks the current byte being sent
volatile size_t bytes_sent_in_1s = 0;   // Counts the bytes sent in 1 second
// Define the text
const char TEXT[] =
    "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting "
    "that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking "
    "action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial "
    "crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan "
    "waivers, saying that they could be the sources of next banking crisis. Government should focus on sources "
    "of the next crisis, not just the last one. "
    "In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit "
    "targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future "
    "NPAs,\" Rajan said in the note.\" Both MUDRA loans as well as the Kisan Credit Card, while popular, have to "
    "be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September "
    "2016, is currently.";

// void write_uart(void)
// {
//     Uart_HAL_SendData(UART_NUM_1, (uint8_t *)TEXT, strlen(TEXT));
// }

// void write_uart(void)
// {
//     size_t text_length = strlen(TEXT);
//     size_t chunk_size = 64; // Adjust chunk size based on UART driver buffer
//     size_t static offset = 0;

//     while (offset < text_length)
//     {
//         // Calculate remaining bytes to send
//         size_t bytes_to_send = (text_length - offset > chunk_size) ? chunk_size : text_length - offset;

//         // Send the current chunk
//         Uart_HAL_SendData(UART_NUM_1, (uint8_t *)&TEXT[offset], bytes_to_send);

//         // Update offset for the next chunk
//         offset += bytes_to_send;

//         // Optional: Add a small delay to ensure UART handles the chunks smoothly
//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }
bool transmission_complete = false;
void write_uart(void)
{
    if (current_byte_index < strlen(TEXT))
    {
        // Send the current byte
        Uart_HAL_SendData(UART_NUM_1, (uint8_t *)&TEXT[current_byte_index], 1);

        // Update counters
        current_byte_index++;
        bytes_sent_in_1s++;
    }
    else
    {
        // Reset index if all bytes are sent
        current_byte_index = 0;
        // printf("All bytes sent. Terminating transmission.\n");
        transmission_complete = true; // Set the flag to prevent further prints
        // return;
    }
}

void read_uart(void)
{
    static uint16_t offset = 0; // Keeps track of where to store the next byte
    uint8_t received_byte;

    // Receive one byte
    Uart_HAL_ReceiveData(uart_num, &received_byte, 1);
    {
        // Write the received byte into EEPROM
        if (write_TripID_byte_eeprom(received_byte, offset) == ESP_OK)
        {
            printf("Stored byte 0x%02X at offset %d\n", received_byte, offset);
            offset++; // Increment offset for the next byte
        }
        else
        {
            printf("Failed to store byte 0x%02X at offset %d\n", received_byte, offset);
        }
    }
    // else
    // {
    //     printf("Failed to receive byte from UART.\n");
    // }
}

void print_uart()
{
    printf(
        "RX data:");

    for (int i = 0; i < 21; i++)
    {
        printf("%C,", uart_payload[i]);
    }

    printf("\n");
}

// void write_uart(void)
// {

//     Uart_HAL_SendData(uart_num, uart_payload, UART_TX_DATA_LEN);
// }

// void read_uart(void)
// {
//     Uart_HAL_ReceiveData(uart_num, (uint8_t *)uart_payload, 1);
//     write_TripID_eeprom()
// }