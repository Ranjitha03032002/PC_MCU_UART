// timer_mngr.c

#include "timer_mngr.h"

void start_timer()
{
    esp_timer_start_periodic(indicate_timer, time_interval); // 1 second interval (in microseconds)
    // init_black_box();
}

void stop_timer()
{
    esp_timer_stop(indicate_timer);
    // esp_timer_stop(odo_timer);
}
