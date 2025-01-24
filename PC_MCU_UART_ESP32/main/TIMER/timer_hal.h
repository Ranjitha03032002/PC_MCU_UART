#ifndef TIMER_HAL_H
#define TIMER_HAL_H

#include "esp_timer.h"
#include "timer_conf.h"

extern void setup_indication_timer();

extern esp_timer_handle_t indicate_timer;
extern uint8_t counter;

#endif // TIMER_HAL_H
