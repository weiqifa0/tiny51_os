/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"

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
  TINY51_OS_GPIO1_8 = !TINY51_OS_GPIO1_8;
}

void main(void)
{
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
  for (;;)
  {
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
