#include "driver/gpio.h"
#include "Arduino.h"
#include "driver/timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

QueueHandle_t Queue;
uint32_t isr_count = 0;

#define TIMER_GROUP TIMER_GROUP_0
#define TIMER_IDX TIMER_0

void init_queue(){
    Queue = xQueueCreate(10,sizeof(uint32_t));   //Create a queue with depth 10 and item size of uint32_t
}

void IRAM_ATTR onTimerISR(void* arg) {

    timer_group_clr_intr_status_in_isr(TIMER_GROUP, TIMER_IDX);
    timer_group_enable_alarm_in_isr(TIMER_GROUP, TIMER_IDX);

    isr_count++;   //increment count

    //Send data every 2000 interrupts
    if (isr_count % 2000 == 0)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;   //Default:no higher priority task token

        xQueueSendFromISR(Queue,&isr_count,&xHigherPriorityTaskWoken);    //Call the interrupt-safe API to send data
    }
}
