/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"
#include "drivers/lcd1602.h"

void task0(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_0 = !TINY51_OS_GPIO1_0;
    platform_delay_xms(100);
  }
}

void task1(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
    platform_delay_xms(800);
  }
}

void task2(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
    platform_delay_xms(1000);
  }
}

void main(void)
{
  //lcd1602_init();
  // lcd1602_position_x_y(0);
  // lcd1602_write_string(5, 0, "Happy");
  // lcd1602_write_string(5, 1, "10.1");
  platform_timer_init_10ms();
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling(1, task0);
  tiny51_register_task_scheduling(2, task1);
  tiny51_register_task_scheduling(3, task2);
  tiny51_task_start(0);
  while (1)
  {
    TINY51_OS_GPIO1_3 = !TINY51_OS_GPIO1_3;
  }

}

void platform_timer_init_10ms_interrupt(void) __interrupt(1)
{
  PLATFORM_OPEN_IRQ(0);

  TH0 = 0xD8;
  TL0 = 0xF0;

  // __asm__("PUSH ACC");
  // __asm__("PUSH B");
  // __asm__("PUSH PSW");
  // __asm__("PUSH DPL");
  // __asm__("PUSH DPH");
  // __asm__("PUSH ar0");
  // __asm__("PUSH ar1");
  // __asm__("PUSH ar2");
  // __asm__("PUSH ar3");
  // __asm__("PUSH ar4");
  // __asm__("PUSH ar5");
  // __asm__("PUSH ar6");
  // __asm__("PUSH ar7");

  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_current_task()].status = TINY51_OS_STATUS_READY;
  tiny51_task[tiny51_get_next_task()].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;

  // __asm__("POP ar7");
  // __asm__("POP ar6");
  // __asm__("POP ar5");
  // __asm__("POP ar4");
  // __asm__("POP ar3");
  // __asm__("POP ar2");
  // __asm__("POP ar1");
  // __asm__("POP ar0");
  // __asm__("POP DPH");
  // __asm__("POP DPL");
  // __asm__("POP PSW");
  // __asm__("POP B");
  // __asm__("POP ACC");
  // __asm__("RET");

  PLATFORM_OPEN_IRQ(1);
  PLATFORM_NOP(1);
}
