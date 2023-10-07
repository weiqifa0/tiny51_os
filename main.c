/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"

void task0(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_0 = !TINY51_OS_GPIO1_0;
    platform_delay_xms(1);
  }
}

void task1(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
    platform_delay_xms(2);
  }
}

void task2(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
    platform_delay_xms(3);
  }
}

void main(void)
{
  platform_timer_init_1ms();
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling(0, task0);
  tiny51_register_task_scheduling(1, task1);
  tiny51_register_task_scheduling(2, task2);
  tiny51_task_start(0);
}

void platform_timer_init_10ms_interrupt(void) __interrupt(1)
{
  EA = 0;
  TH0 = 0xD8;
  TL0 = 0xF0;
  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_current_task()].status = READY_STATUS;
  tiny51_task[tiny51_get_next_task()].status = RUN_STATUS;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;
  TINY51_OS_GPIO1_7 = !TINY51_OS_GPIO1_7;

  EA = 1;

  __asm;
  nop
      __endasm;
}
