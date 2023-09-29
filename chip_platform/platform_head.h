/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __PLATFORM_HEAD_H
#define __PLATFORM_HEAD_H

#include "stc89c52.h"

#define TINY51_OS_GPIO1_1 P1_0
#define TINY51_OS_GPIO1_2 P1_1
#define TINY51_OS_GPIO1_3 P1_2
#define TINY51_OS_GPIO1_4 P1_3

void tiny51_os_timer_init(void);
typedef int (*tiny51_os_callback)(void);
int set_timer_irq_callback_function(tiny51_os_callback m_timer_irq_function);
int UpdateTimers(void);

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

#define RAM_RANGE_IDATA __idata

#endif //__PLATFORM_HEAD_H