/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "key.h"

void key_gpio_init(void)
{
  platform_set_gpio_mode(3, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT);
  platform_set_gpio_mode(4, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT);
  platform_set_gpio_mode(5, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT);
}
bool get_sw1_key_pressed(void)
{
  if (P3_2 == FALSE) {
    return TRUE;
  }
  return FALSE;
}