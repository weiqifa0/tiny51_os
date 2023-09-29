/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"

// ============================以下为测试代码============================

void task1()
{
  static int i = 0;
  while(1)
  {
    //if (tast1_delay_ms >= TASK_1_SLEEP_MS)
    {
      if (i++ >= 300) {
        TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
        i = 0;
      }
    }
    tiny51_task_scheduling();//编译后在这里打上断点
  }
}

void task2()
{
  static int j = 0;
  while(1)
  {
    if (j++ >= 4000)
    {
      j = 0;
      TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
    }
    tiny51_task_scheduling();//编译后在这里打上断点
  }
}

void task3()
{
  static int j = 0;
  while(1)
  {
    if (j++ >= 400)
    {
      j = 0;
      TINY51_OS_GPIO1_3 = !TINY51_OS_GPIO1_3;
    }
    tiny51_task_scheduling();//编译后在这里打上断点
  }
}

void task4()
{
  static int j = 0;
  while(1)
  {
    if (j++ >= 6000)
    {
      j = 0;
      TINY51_OS_GPIO1_4 = !TINY51_OS_GPIO1_4;
    }
    tiny51_task_scheduling();//编译后在这里打上断点
  }
}

void main()
{
  register_task_scheduling((unsigned int)task1, (unsigned char)0);
  register_task_scheduling((unsigned int)task2, (unsigned char)1);
  register_task_scheduling((unsigned int)task3, (unsigned char)2);
  register_task_scheduling((unsigned int)task4, (unsigned char)3);
  start_task_scheduling(0);
}

