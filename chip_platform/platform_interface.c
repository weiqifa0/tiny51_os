/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "platform_head.h"

void platform_timer_init_10ms(void)
{
	TMOD = 0x01;
	/*晶振是 11.0592MHz，定时时间为：10ms TH0 = 0xDC  TL0 = 0x00  1ms TH0 = 0xFC  TL0 = 0x66 */
	/*晶振是 12MHz     ，定时时间为：10ms TH0 = 0xD8  TL0 = 0xF0  1ms TH0 = 0xFC  TL0 = 0x18 */
	TH0 = 0xD8;
	TL0 = 0xF0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void platform_delay_xms(unsigned int ms)		//@11.0592MHz
{
  unsigned char i, j;

  while (ms--) {
    __asm__("nop");
    i = 2;
    j = 199;
    do {
      while (--j);
    } while (--i);
  }
}