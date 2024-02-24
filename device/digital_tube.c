/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "digital_tube.h"

void digital_tube_gpio_init(void)
{
  platform_set_gpio_mode(4, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(5, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );

  platform_set_gpio_mode(7, 7, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(4, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(7, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(7, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(5, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(0, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );

  platform_set_gpio_value(4, 5, GPIO_HIGH);
  platform_set_gpio_value(5, 2, GPIO_HIGH);
  platform_set_gpio_value(0, 4, GPIO_HIGH);
  platform_set_gpio_value(0, 1, GPIO_HIGH);

  //platform_set_gpio_value(7, 7, GPIO_HIGH);
  platform_set_gpio_value(4, 6, GPIO_HIGH);
  platform_set_gpio_value(0, 3, GPIO_HIGH);
  //platform_set_gpio_value(7, 5, GPIO_HIGH);
  //platform_set_gpio_value(7, 6, GPIO_HIGH);
  platform_set_gpio_value(0, 0, GPIO_HIGH);
  platform_set_gpio_value(5, 3, GPIO_HIGH);
  platform_set_gpio_value(0, 2, GPIO_HIGH);
}

