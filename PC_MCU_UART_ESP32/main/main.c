// main.c
#include "sdkconfig.h"
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "eeprom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "timer.h"
#include "uart.h"

TaskHandle_t Global_Loop;

void func(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // 100 ms
    // printf("************************ func running  ***************************************");
    while (true)
    {
        counter++;
        write_uart();
        // printf("************************ func running  ***************************************");
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

int app_main(void)
{
    uart_1_init();
    EEPROM_Init();
    setup_indication_timer();
    erase_eeprom();
    printf("ResetGOING ON ***************************************\n");
    while (1)
    {
        write_uart();
    }
    return 0;
}

// printf("ResetGOING ON ***************************************\n");
// read_TripID_bytes_eeprom(0, 0);
// read_uart_and_store_in_eeprom();
// Read back the 10 bytes from EEPROM
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

// // // End of the application
// // printf("EEPROM test complete.\n");
// // // Write 10 bytes to EEPROM
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
// while (1)
// {
// write_uart();
// // if (transmission_complete)
// // {
// //     break;
// // }
// // read_uart();
// // print_uart();
// // xTaskCreatePinnedToCore(func, "update_task", 4096, NULL, tskIDLE_PRIORITY, &Global_Loop, 1);'
// Uart_HAL_ReceiveData(UART_NUM_1, &received_byte, 1);
// // return 0;
// }
// return 0;
// while (!reception_complete) // Keep receiving until the process is complete
// {
// Uart_HAL_ReceiveData(UART_NUM_1, &received_byte, 1);
// }

// Perform EEPROM read once all bytes are received
// printf("Reception complete. Reading data from EEPROM...\n");
// uint8_t eeprom_data[MAX_BYTES];
// read_TripID_bytes_eeprom(0, 0);

// // Print or process the read data
// // for (int i = 0; i < received_count; i++)
// // {
// //     printf("%c", eeprom_data[i]);
// // }
// printf("\nAll data read from EEPROM.\n");