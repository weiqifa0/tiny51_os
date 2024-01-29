/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "led.h"

void led_init(void)
{
  // gpio led init
  platform_set_gpio_mode(0, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 7, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(1, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(6, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
}

void set_led_num(uint8_t led_num, uint8_t on)
{
  switch (led_num)
  {
  case 1:
  platform_set_gpio_value(0, 5, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 2:
  platform_set_gpio_value(0, 6, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 3:
  platform_set_gpio_value(0, 7, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 4:
  platform_set_gpio_value(6, 0, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 5:
  platform_set_gpio_value(6, 1, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 6:
  platform_set_gpio_value(6, 2, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 7:
  platform_set_gpio_value(1, 0, on ? GPIO_LOW : GPIO_HIGH);
  break;
  case 8:
  platform_set_gpio_value(6, 3, on ? GPIO_LOW : GPIO_HIGH);
  break;
  default:
    break;
  }
}