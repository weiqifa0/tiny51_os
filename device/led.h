/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#ifndef __LED_H
#define __LED_H

#include "../chip_platform/platform_head.h"

void led_init(void);
void set_led_num(uint8_t led_num, bool on);

#endif // __LED_H