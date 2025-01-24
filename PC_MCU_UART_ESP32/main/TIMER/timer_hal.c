// timer_hal.c

#include "timer_hal.h"
#include "uart_mngr.h"

esp_timer_handle_t indicate_timer;
esp_timer_handle_t odo_timer;
uint8_t counter = 0;
void indicate_timer_callback(void *arg)
{
    // printf("Bytes sent in last 2 second: %zu\n", bytes_sent_in_1s);

    // Reset the byte counter for the next second
    bytes_sent_in_1s = 0;
}

void odo_timer_callback(void *arg)
{
    // ++counter_passed;
}

void setup_indication_timer()
{
    const esp_timer_create_args_t indicate_timer_args = {
        .callback = &indicate_timer_callback,
        .name = "indicate_timer"};

    esp_err_t timer_ret = esp_timer_create(&indicate_timer_args, &indicate_timer);
    if (timer_ret != ESP_OK)
    {
        // ESP_LOGE(GATTS_TABLE_TAG, "Failed to create timer: %s", esp_err_to_name(timer_ret));
        // Handle the error.
    }
    else
    {
        printf("Timer Created - indicate\r\n");
    }
    esp_timer_start_periodic(indicate_timer, 2000000);

    const esp_timer_create_args_t odo_timer_args = {
        .callback = &odo_timer_callback,
        .name = "odo_timer"};

    timer_ret = esp_timer_create(&odo_timer_args, &odo_timer);
    if (timer_ret != ESP_OK)
    {
        // ESP_LOGE(GATTS_TABLE_TAG, "Failed to create timer: %s", esp_err_to_name(timer_ret));
        // Handle the error.
    }
    else
    {
        printf("Timer Created - odo\r\n");
    }
}
