#include "driver/timer.h"

//Define timer group and timer index
#define TIMER_GROUP TIMER_GROUP_0
#define TIMER_IDX TIMER_0

void init_hardware_timer(){
  //Initialize timer using timer_config_t structure
  timer_config_t config = {
    .alarm_en = TIMER_ALARM_EN,  //Enable alarm(interrupt)
    .intr_type = TIMER_INTR_LEVEL,  //Use level interrupt
    .counter_dir = TIMER_COUNT_UP,  
    .divider = 80
  };

  //Initialize the timer
  timer_init(TIMER_GROUP,TIMER_IDX,&config);

  //Set high-precision trigger period to 500 microseconds
  timer_set_counter_value(TIMER_GROUP,TIMER_IDX,0);
  timer_set_alarm_value(TIMER_GROUP,TIMER_IDX,500);

  //Enable timer interrupt
  timer_enable_intr(TIMER_GROUP,TIMER_IDX);
  timer_start(TIMER_GROUP,TIMER_IDX);
}