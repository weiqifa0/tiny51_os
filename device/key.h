/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __KEY_H
#define __KEY_H
#include "../chip_platform/platform_head.h"

#if COMPLILE_SDCC
  #define KEY_1 P3_2
#elif COMPLILE_KEIL
  #define KEY_1 P32
#endif

void key_gpio_init(void);
uint8_t get_sw1_key_pressed(void);

#endif //__KEY_H