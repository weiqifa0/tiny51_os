/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "platform_head.h"

void platform_timer_init_10ms(void)
{
  TMOD = 0x21;
  IE |= 0x82;
  TH0 = 0XFC; //给定时器赋初值，定时 1ms
  TL0 = 0X18;
  TR0 = 1;
  EA = 1;
}

void platform_delay_xms(uint16_t ms)		//@11.0592MHz
{
  unsigned char i, j;
  while (ms--) {
    __NOP__();
    i = 2;
    j = 199;
    do {
      while (--j);
    } while (--i);
  }
}

void platform_set_gpio_mode(uint8_t gpio_x_num, uint8_t gpio_y_num, enum TINY51_OS_GPIO_MODE mode)
{
  switch (mode)
  {
    case GPIO_GENERAL_PURPOSE_INPUT_OUTPUT :
      SET_REGISTER_M0_VALUE(gpio_x_num, gpio_y_num, 0);
      SET_REGISTER_M1_VALUE(gpio_x_num, gpio_y_num, 0);
      break;
    case GPIO_PUSH_PULL_OUTPUT:
      SET_REGISTER_M0_VALUE(gpio_x_num, gpio_y_num, 1);
      SET_REGISTER_M1_VALUE(gpio_x_num, gpio_y_num, 0);
      break;
    case GPIO_HIGH_INPEDANCE_INPUT:
      SET_REGISTER_M0_VALUE(gpio_x_num, gpio_y_num, 0);
      SET_REGISTER_M1_VALUE(gpio_x_num, gpio_y_num, 1);
      break;
    case GPIO_OPEN_COLLECTOR_OUTPUT:
      SET_REGISTER_M0_VALUE(gpio_x_num, gpio_y_num, 1);
      SET_REGISTER_M1_VALUE(gpio_x_num, gpio_y_num, 1);
      break;
    default:
      break;
  }
}

void platform_set_gpio_pull_up_resister(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t value)
{
  SET_REGISTER_PU_VALUE(gpio_x_num, gpio_y_num, value);
}

void platform_set_gpio_value(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t gpio_value)
{
  SET_GPIO_OUTPUT_VALUE(gpio_x_num, gpio_y_num, gpio_value);
}

void platform_set_gpio_driver_capability(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t value)
{
  SET_GPIO_DRIVE_CAPABILITY(gpio_x_num, gpio_y_num, value);
}