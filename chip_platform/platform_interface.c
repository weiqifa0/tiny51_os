/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "platform_head.h"

tiny51_os_callback p_timer_irq_function = NULL;

void tiny51_os_timer_init(void)
{
  TMOD = 0x21;
  IE |= 0x82;
  TL0 = 0Xff;
  TH0 = 0XDB;
  TR0 = 1;
}

int tiny51_os_timer_irq_handle(tiny51_os_callback x)
{
  x();
  return 0;
}

int set_timer_irq_callback_function(tiny51_os_callback m_timer_irq_function)
{
  if (m_timer_irq_function != NULL)
  {
    p_timer_irq_function = m_timer_irq_function;
  }
  return 0;
}
