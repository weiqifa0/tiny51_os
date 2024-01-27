/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __KEY_H
#define __KEY_H
#include "../chip_platform/platform_head.h"
#include "../machine_hal/machine_config.h"

void key_gpio_init(void);
bool get_sw1_key_pressed(void);

#endif //__KEY_H