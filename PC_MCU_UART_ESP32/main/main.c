// main.c
#include "sdkconfig.h"
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "uart_mngr.h"
#include "uart_conf.h"
#include "eeprom_hal.h"
#include "eeprom_mngr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "timer_hal.h"
#include "timer_mngr.h"

TaskHandle_t Global_Loop;

void func(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(2000); // 100 ms
    // printf("************************ func running  ***************************************");
    while (true)
    {
        counter++;
        write_uart();
        print_uart();
        // printf("************************ func running  ***************************************");
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void read_uart_and_store_in_eeprom(void)
{
    uint8_t received_byte = 0; // Variable to hold the received byte
    uint32_t offset = 0;       // EEPROM offset

    printf("Starting UART read and EEPROM store...\n");

    // while (1)
    for (int i = 0; i < 500; i++)
    {
        // Read one byte from UART
        Uart_HAL_ReceiveData(UART_NUM_1, &received_byte, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        // if (uart_ret == ESP_OK)
        {
            printf("Received byte: %c (0x%02X), storing at EEPROM offset %ld\n", received_byte, received_byte, offset);

            // Store the received byte in EEPROM
            esp_err_t eeprom_ret = write_TripID_byte_eeprom(received_byte, offset);
            vTaskDelay(pdMS_TO_TICKS(100));
            if (eeprom_ret == ESP_OK)
            {
                printf("Stored byte at offset %ld\n", offset);
            }
            else
            {
                printf("Failed to store byte at offset %ld. Error: %d\n", offset, eeprom_ret);
            }

            offset++; // Increment offset for the next byte
        }
        // else
        // {
        //     printf("UART read error. Retrying...\n");
        // }
    }
    // for (int i = 0; i < 1100; i++)
    {
        esp_err_t ret = read_TripID_bytes_eeprom(received_byte, 1);
        // printf("%d ", received_byte);
    }
}

int app_main(void)
{
    uint8_t received_byte = 0; // Variable to hold the received byte
    uart_1_init();
    EEPROM_Init();
    setup_indication_timer();
    // start_timer();
    // erase_eeprom();
    printf("ResetGOING ON ***************************************\n");
    // read_uart_and_store_in_eeprom();
    // // Read back the 10 bytes from EEPROM
    // uint8_t read_buffer[10] = {0}; // Buffer to hold read data
    // esp_err_t ret = read_TripID_bytes_eeprom(read_buffer, 10);

    // if (ret == ESP_OK)
    // {
    //     printf("Successfully read bytes from EEPROM: ");
    //     for (int i = 0; i < 10; i++)
    //     {
    //         printf("%d ", read_buffer[i]);
    //     }
    //     printf("\n");
    // }
    // else
    // {
    //     printf("Failed to read bytes from EEPROM. Error: %d\n", ret);
    // }

    // // End of the application
    // printf("EEPROM test complete.\n");
    // // Write 10 bytes to EEPROM
    // for (int i = 0; i < 10; i++)
    // {
    //     esp_err_t ret = write_TripID_byte_eeprom(0, i); // Write index `i` as the value
    //     if (ret == ESP_OK)
    //     {
    //         printf("Successfully wrote byte %d at offset %d\n", i, i);
    //     }
    //     else
    //     {
    //         printf("Failed to write byte %d at offset %d. Error: %d\n", i, i, ret);
    //     }
    // }

    // ret = read_TripID_bytes_eeprom(read_buffer, 10);
    // if (ret == ESP_OK)
    // {
    //     printf("Successfully read bytes from EEPROM: ");
    //     for (int i = 0; i < 10; i++)
    //     {
    //         printf("%d ", read_buffer[i]);
    //     }
    //     printf("\n");
    // }
    // else
    // {
    //     printf("Failed to read bytes from EEPROM. Error: %d\n", ret);
    // }
    // // Write 10 bytes to EEPROM
    // for (int i = 0; i < 10; i++)
    // {
    //     esp_err_t ret = write_TripID_byte_eeprom(i, i); // Write index `i` as the value
    //     if (ret == ESP_OK)
    //     {
    //         printf("Successfully wrote byte %d at offset %d\n", i, i);
    //     }
    //     else
    //     {
    //         printf("Failed to write byte %d at offset %d. Error: %d\n", i, i, ret);
    //     }
    // }

    // ret = read_TripID_bytes_eeprom(read_buffer, 10);
    // if (ret == ESP_OK)
    // {
    //     printf("Successfully read bytes from EEPROM: ");
    //     for (int i = 0; i < 10; i++)
    //     {
    //         printf("%d ", read_buffer[i]);
    //     }
    //     printf("\n");
    // }
    // else
    // {
    //     printf("Failed to read bytes from EEPROM. Error: %d\n", ret);
    // }
    // // End of the application
    // printf("EEPROM test complete.\n");

    // ptint whatever read from eeprom
    while (1)
    {
        // write_uart();
        // if (transmission_complete)
        // {
        //     break;
        // }
        // read_uart();
        // print_uart();
        // xTaskCreatePinnedToCore(func, "update_task", 4096, NULL, tskIDLE_PRIORITY, &Global_Loop, 1);'
        Uart_HAL_ReceiveData(UART_NUM_1, &received_byte, 1);
        // return 0;
    }
    return 0;
}
