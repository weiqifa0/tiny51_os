/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __PLATFORM_HEAD_H
#define __PLATFORM_HEAD_H

#include "platform_type.h"
#include "stc89c52.h"

#define CPU_MCLK 110592 //HZ

#define TINY51_OS_GPIO1_1 P1_0
#define TINY51_OS_GPIO1_2 P1_1
#define TINY51_OS_GPIO1_3 P1_2
#define TINY51_OS_GPIO1_4 P1_3
#define TINY51_OS_GPIO1_5 P1_4
#define TINY51_OS_GPIO1_6 P1_5
#define TINY51_OS_GPIO1_7 P1_6
#define TINY51_OS_GPIO1_8 P1_7

void platform_timer_init_1ms(void);

#define RAM_RANGE_IDATA __idata

#endif //__PLATFORM_HEAD_H