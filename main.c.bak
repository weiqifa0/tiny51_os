/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"
#include "drivers/lcd1602.h"

void task1(void)
{
  // while(1)
  {
    TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
    // tiny51_task_scheduling();
  }
}

void task2(void)
{
  // while(1)
  {
    TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
    // tiny51_task_scheduling();
  }
}

void task3(void)
{
  // while(1)
  {
    TINY51_OS_GPIO1_3 = !TINY51_OS_GPIO1_3;
    // tiny51_task_scheduling();
  }
}

void task4(void)
{
  // while(1)
  {
    TINY51_OS_GPIO1_4 = !TINY51_OS_GPIO1_4;
    // tiny51_task_scheduling();
  }
}

void task5(void)
{
  TINY51_OS_GPIO1_5 = !TINY51_OS_GPIO1_5;
}

void task6(void)
{
  TINY51_OS_GPIO1_6 = !TINY51_OS_GPIO1_6;
}

void task7(void)
{
  TINY51_OS_GPIO1_7 = !TINY51_OS_GPIO1_7;
}

void task8(void)
{
  TINY51_OS_GPIO1_0 = !TINY51_OS_GPIO1_0;
}

void main(void)
{
  lcd1602_init();
  lcd1602_position_x_y(0);
  lcd1602_write_string(5, 0, "Happy");
  lcd1602_write_string(5, 1, "10.1");
  platform_timer_init_1ms();
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