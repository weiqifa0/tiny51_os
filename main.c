/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"
#include "drivers/lcd1602.h"
#include "drivers/uart.h"

void task0(void)
{
  while (1)
  {
    //uart_write('1');
    platform_set_gpio_value(0, 7, GPIO_HIGH);
    platform_delay_xms(300);
    platform_set_gpio_value(0, 7, GPIO_LOW);
    platform_delay_xms(300);
  }
}

void task1(void)
{
  while (1)
  {

    //uart_write('1');
    platform_set_gpio_value(0, 6, GPIO_HIGH);
    platform_delay_xms(300);
    platform_set_gpio_value(0, 6, GPIO_LOW);
    platform_delay_xms(300);
  }
}

void task2(void)
{
  while (1)
  {
    platform_set_gpio_value(0, 5, GPIO_LOW);
    //uart_write('2');
    platform_delay_xms(1000);
    platform_set_gpio_value(0, 5, GPIO_HIGH);
    platform_delay_xms(1000);
  }
}

void tiny51_gpio_init(void)
{
  // gpio init
  platform_set_gpio_mode(0, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 7, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(1, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );

  // lcd BL
  platform_set_gpio_mode(7, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_pull_up_capacity(7, 4, 1);
  platform_set_gpio_value(7, 4, GPIO_HIGH);

  // 1602 gpio init
  platform_set_gpio_mode(4, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(4, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(4, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 7, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
}

void main(void)
{
  tiny51_gpio_init();
  lcd1602_init();
  // lcd1602_write_char(5, 0, '1');
  // lcd1602_write_char(6, 0, '9');
  // lcd1602_write_char(7, 0, '6');
  // lcd1602_write_char(8, 0, '4');
  // lcd1602_write_char(5, 1, 'l');
  // lcd1602_write_char(6, 1, 'a');
  // lcd1602_write_char(7, 1, 'b');
  lcd1602_write_string(0, 0, "12:51");
  lcd1602_write_string(0, 1, "1964Lab");

  platform_timer_init_10ms();
  uart_init();
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling(1, task0);
  tiny51_register_task_scheduling(2, task1);
  tiny51_register_task_scheduling(3, task2);
  tiny51_task_start(0);
  while (1)
  {
    // /* code */
    // // P0M0 = 0x00;
    // // P0M1 = 0x00;
    // //uart_write('t');
    // platform_set_gpio_value(0, 5, GPIO_LOW);
    // platform_set_gpio_value(0, 6, GPIO_LOW);
    // platform_set_gpio_value(0, 7, GPIO_LOW);
    // platform_set_gpio_value(6, 0, GPIO_LOW);
    // platform_set_gpio_value(6, 1, GPIO_LOW);
    // platform_set_gpio_value(6, 2, GPIO_LOW);
    // platform_set_gpio_value(1, 0, GPIO_LOW);
    // platform_set_gpio_value(6, 3, GPIO_LOW);
    // platform_delay_xms(1000);
    // platform_set_gpio_value(0, 5, GPIO_HIGH);
    // platform_set_gpio_value(0, 6, GPIO_HIGH);
    // platform_set_gpio_value(0, 7, GPIO_HIGH);
    // platform_set_gpio_value(6, 0, GPIO_HIGH);
    // platform_set_gpio_value(6, 1, GPIO_HIGH);
    // platform_set_gpio_value(6, 2, GPIO_HIGH);
    // platform_set_gpio_value(1, 0, GPIO_HIGH);
    // platform_set_gpio_value(6, 3, GPIO_HIGH);
    // platform_delay_xms(1000);
  }

}

void platform_timer_init_10ms_interrupt(void) __interrupt(1)
{
  PLATFORM_OPEN_IRQ(0);

  TH0 = 0xD8;
  TL0 = 0xF0;
  // 进入中断后，系统给每个任务task分配一个私有的栈，这个SP就是指向这个私有的栈，之后的切换都是在这个私有的栈中进行
  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_current_task()].status = TINY51_OS_STATUS_READY;
  tiny51_task[tiny51_get_next_task()].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;

  PLATFORM_OPEN_IRQ(1);
}

void platform_uart_interrupt(void) __interrupt(4)
{
  RI = 0;
  P1 = SBUF;
}