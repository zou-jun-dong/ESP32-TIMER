#include "driver/gpio.h"
#include "Arduino.h"
#include "driver/timer.h"

#define TEST_GPIO GPIO_NUM_2
#define TIMER_GROUP TIMER_GROUP_0
#define TIMER_IDX TIMER_0

void IRAM_ATTR onTimerISR(void* arg) {

    timer_group_clr_intr_status_in_isr(TIMER_GROUP, TIMER_IDX);
    timer_group_enable_alarm_in_isr(TIMER_GROUP, TIMER_IDX);

    uint32_t current_level = gpio_get_level(TEST_GPIO);
    gpio_set_level(TEST_GPIO, !current_level);
}
