#include "uart.h"
#include "eeprom.h"

const uart_port_t uart_num = UART_NUM_1;

uart_config_t uart_config = {
    .baud_rate = 2400,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
};

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

volatile size_t current_byte_index = 0;
volatile size_t bytes_sent_in_1s = 0;
volatile bool transmission_complete = false;
volatile bool reception_complete = false;
uint8_t received_data_buffer[MAX_RECEIVE_BUFFER_SIZE];
size_t received_data_index = 0;
uint8_t termination_buffer[TERMINATION_LENGTH] = {0};
volatile size_t offset = 0;

void uart_1_init(void)
{

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_1_TX, UART_1_RX, UART_1_RTS, UART_1_CTS));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_1_RX_BUFF, UART_1_TX_BUFF, 0, NULL, 0));

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

void write_uart(void)
{
    if (current_byte_index < strlen(TEXT))
    {
        Uart_HAL_SendData(UART_NUM_1, (uint8_t *)&TEXT[current_byte_index], 1);
        current_byte_index++;
        bytes_sent_in_1s++;
    }
    else
    {
        // When all bytes are sent,
        current_byte_index = 0;
        transmission_complete = true;
    }
}

void read_uart(void)
{
    static uint16_t offset = 0;
    uint8_t received_byte;

    Uart_HAL_ReceiveData(uart_num, &received_byte, 1);
    {
        if (write_TripID_byte_eeprom(received_byte, offset) == ESP_OK)
        {
            printf("Stored byte 0x%02X at offset %d\n", received_byte, offset);
            offset++;
        }
        else
        {
            printf("Failed to store byte 0x%02X at offset %d\n", received_byte, offset);
        }
    }
}

void Uart_HAL_ReceiveData(uint32_t instance, uint8_t *RxPayload, uint8_t Payload_Size)
{
    int bytes_read = uart_read_bytes(instance, RxPayload, Payload_Size, 40);
    if (bytes_read >= 1)
    {
        printf("%c", *RxPayload);

        if (received_data_index < MAX_RECEIVE_BUFFER_SIZE)
        {
            received_data_buffer[received_data_index++] = *RxPayload;
        }
        else
        {
            printf("Buffer overflow! Data truncated.\n");
        }

        esp_err_t eeprom_ret = write_TripID_byte_eeprom(RxPayload, offset);
        if (eeprom_ret == ESP_OK)
        {
            printf("Stored byte at offset %d\n", offset);
        }
        offset++;

        memmove(termination_buffer, termination_buffer + 1, TERMINATION_LENGTH - 1);
        termination_buffer[TERMINATION_LENGTH - 1] = *RxPayload;

        if (memcmp(termination_buffer, TERMINATION_SEQUENCE, TERMINATION_LENGTH) == 0)
        {
            reception_complete = true;
            printf("\nReception complete. Received data:\n");
            for (size_t i = 0; i < received_data_index; i++)
            {
                printf("%c", received_data_buffer[i]);
            }
            printf("\n");
        }
    }
}