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

void main()
{
  //这里装载了两个任务,因此在定义MAX_TASKS时也必须定义为2
  task_load((unsigned int)task1, (unsigned char)0);//将task1函数装入0号槽
  task_load((unsigned int)task2, (unsigned char)1);//将task2函数装入1号槽
  // timer0_init();
  os_start(0);
}

