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

void main(void)
{
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling((unsigned int)task1, 4000);
  tiny51_register_task_scheduling((unsigned int)task2, 2000);
  tiny51_register_task_scheduling((unsigned int)task3, 900);
  tiny51_register_task_scheduling((unsigned int)task4, 700);
  for (;;)
  {
    tiny51_task_scheduling();
  }
}

