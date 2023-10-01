/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "platform_head.h"

void platform_timer_init_1ms(void)
{
  TMOD = 0x21;
  IE |= 0x82;
  TH0 = 0XFC; //给定时器赋初值，定时 1ms
  TL0 = 0X18;
  TR0 = 1;
  EA = 1;
}

void platform_delay_xms(uint16_t x)		//@11.0592MHz
{
  uint16_t i, j;
  while (x--)
  {
    PLATFORM_NOP(1);
    i = 2;
    j = 199;
    do {
      while (--j);
    } while (--i);
  }
}