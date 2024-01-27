/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"
#include "device/lcd1602.h"
#include "device/uart.h"
#include "device/key.h"
#include "module/ring_buff.h"
#include "device/led.h"

void task1(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(1, TRUE);
  }
  else
  {
    set_led_num(1, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task2(void)
{
  set_led_num(2, TRUE);
}

void task3(void)
{
  set_led_num(3, TRUE);
}

void task4(void)
{
  set_led_num(4, TRUE);
}

void task5(void)
{
  set_led_num(5, TRUE);
}

void task6(void)
{
  set_led_num(6, TRUE);
}

void task7(void)
{
  set_led_num(7, TRUE);
}

void task8(void)
{
 set_led_num(8, TRUE);
}

void main(void)
{
  led_init();
  lcd1602_init();
  lcd1602_position_x_y(0);
  lcd1602_write_string(5, 0, "LAB1964");

  platform_timer_init_10ms();
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling((unsigned int)task1, 3000);
  tiny51_register_task_scheduling((unsigned int)task2, 200);
  tiny51_register_task_scheduling((unsigned int)task3, 1000);
  tiny51_register_task_scheduling((unsigned int)task4, 700);
  tiny51_register_task_scheduling((unsigned int)task5, 3000);
  tiny51_register_task_scheduling((unsigned int)task6, 200);
  tiny51_register_task_scheduling((unsigned int)task7, 1000);
  tiny51_register_task_scheduling((unsigned int)task8, 700);
  for (;;) {
    tiny51_task_scheduling();
  }
}

void platform_timer_init_10us_interrupt(void)	__interrupt (1)
{
  int i;
  for (i = 0; i < scheduling_core_t.register_task_count; i++) {
    scheduling_core_t.task_sp[i].heartbeat_count_per_1ms++;
  }

  TH0 = 0XFC;
  TL0 = 0X18;
}