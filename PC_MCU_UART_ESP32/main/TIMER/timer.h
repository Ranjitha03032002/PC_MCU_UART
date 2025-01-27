#ifndef TIMER_H
#define TIMER__H

#include "esp_timer.h"
#include "stdint.h"

extern void setup_indication_timer();

extern esp_timer_handle_t indicate_timer;
extern uint8_t counter;

#endif // TIMER_H
