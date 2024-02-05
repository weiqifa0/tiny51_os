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
#include "device/eeprom.h"
#include "device/m1601.h"

#include <stdio.h>

#define VERSION ("V1.1.1.4")

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
  char buffer[32];
  uint16_t temp_int;
  float temp = read_temp_from_m1601();
  temp_int = temp * 100; // 2548
  lcd1602_write_char(5, 1, temp_int / 1000 + '0');
  lcd1602_write_char(6, 1, temp_int % 1000 / 100 + '0');
  lcd1602_write_char(7, 1, '.');
  lcd1602_write_char(8, 1, temp_int % 100 / 10 + '0');
  lcd1602_write_char(9, 1, temp_int % 100 % 10 + '0'); //
  lcd1602_write_char(10, 1, 'C');
  printf("temp = %bf C\n", temp);
  printf("%s\n", buffer);
}

void task8(void)
{
  char buffer[32];
  uint8_t num1 = eeprom_read_from_address(0x12);

  printf("num1 = 0x%bx\n", num1);

//  memset(&buffer, 0, sizeof(buffer));
//  sprintf(buffer, "EEPROM: 0x12, VAL: %.2X", (uint8_t)num1);
  printf("%s\n", buffer);
}

void main(void)
{
  led_init();

  set_led_num(1, TRUE);
  set_led_num(2, TRUE);
  set_led_num(3, TRUE);
  set_led_num(4, TRUE);
  set_led_num(5, TRUE);
  set_led_num(6, TRUE);
  set_led_num(7, TRUE);
  set_led_num(8, TRUE);

#if TINY51_OS_LCD1602
  lcd1602_gpio_init();
  lcd1602_init();
  lcd1602_position_x_y(0);
  lcd1602_write_string(5, 0, "LAB1964");
#endif
  i2c_interface_init();
  eeprom_init();

  eeprom_write_to_address(0x12, 0xA9);

  platform_timer_init_10ms();
  uart_init();

  m1601_init();

  printf("main start...\n");
  printf("%bs...\n", VERSION);

  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling((unsigned int)task1, 3000);
  tiny51_register_task_scheduling((unsigned int)task2, 200);
  tiny51_register_task_scheduling((unsigned int)task3, 1000);
  tiny51_register_task_scheduling((unsigned int)task4, 700);
  tiny51_register_task_scheduling((unsigned int)task5, 3000);
  tiny51_register_task_scheduling((unsigned int)task6, 200);
  tiny51_register_task_scheduling((unsigned int)task7, 5000);
  tiny51_register_task_scheduling((unsigned int)task8, 2000);

  for (;;) {
    tiny51_task_scheduling();
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
  char read = '\0';
  if (RI) {
    read = SBUF;
    RI = 0;
  }
}
