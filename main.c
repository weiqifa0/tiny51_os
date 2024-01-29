/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#include "chip_platform/platform_head.h"
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
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(2, TRUE);
  }
  else
  {
    set_led_num(2, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task3(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(3, TRUE);
  }
  else
  {
    set_led_num(3, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task4(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(4, TRUE);
  }
  else
  {
    set_led_num(4, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task5(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(5, TRUE);
  }
  else
  {
    set_led_num(5, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task6(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(6, TRUE);
  }
  else
  {
    set_led_num(6, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task7(void)
{
  static uint8_t task1_tmp = 0;
  if (task1_tmp)
  {
    set_led_num(7, TRUE);
  }
  else
  {
    set_led_num(7, FALSE);
  }
  task1_tmp = !task1_tmp;
}

void task8(void)
{
  //uart_write('A');
  platform_delay_xms(1000);
}

void main(void)
{
  uint8_t loop = 1;
  led_init();

  set_led_num(1, TRUE);
  set_led_num(2, TRUE);
  set_led_num(3, TRUE);
  set_led_num(4, TRUE);
  set_led_num(5, TRUE);
  set_led_num(6, TRUE);
  set_led_num(7, TRUE);
  set_led_num(8, TRUE);

  lcd1602_gpio_init();
  lcd1602_init();
  lcd1602_position_x_y(0);
  lcd1602_write_string(5, 0, "LAB1964");

  platform_timer_init_10ms();
  uart_init(115200);

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
    //uart_write_str("1213123124345346456");
    //platform_delay_xms(1000);
  }
}
#if COMPLILE_SDCC
void platform_timer_init_10us_interrupt(void) __interrupt (1)
#elif COMPLILE_KEIL
void platform_timer_init_10us_interrupt(void) interrupt 1
#endif
{
  uint8_t i;
  for (i = 0; i < scheduling_core_t.register_task_count; i++) {
    scheduling_core_t.task_sp[i].heartbeat_count_per_1ms++;
  }

  TH0 = 0XFC;
  TL0 = 0X18;
}

#if COMPLILE_SDCC
void platform_uart_interrupt() __interrupt (4)
#elif COMPLILE_KEIL
void platform_uart_interrupt() interrupt 4
#endif
{
  set_led_num(8, FALSE);
}
