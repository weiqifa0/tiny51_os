/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __PLATFORM_HEAD_H
#define __PLATFORM_HEAD_H

#include "platform_type.h"
//#include "stc89c52.h"
#include "stc8h8k64u.h"

#define CPU_MCLK 110592 //HZ

#define TINY51_OS_GPIO1_0 P1_0
#define TINY51_OS_GPIO1_1 P1_1
#define TINY51_OS_GPIO1_2 P1_2
#define TINY51_OS_GPIO1_3 P1_3
#define TINY51_OS_GPIO1_4 P1_4
#define TINY51_OS_GPIO1_5 P1_5
#define TINY51_OS_GPIO1_6 P1_6
#define TINY51_OS_GPIO1_7 P1_7

#define TINY51_OS_GPIO0_0 P0_0
#define TINY51_OS_GPIO0_1 P0_1
#define TINY51_OS_GPIO0_2 P0_2
#define TINY51_OS_GPIO0_3 P0_3
#define TINY51_OS_GPIO0_4 P0_4
#define TINY51_OS_GPIO0_5 P0_5
#define TINY51_OS_GPIO0_6 P0_6
#define TINY51_OS_GPIO0_7 P0_7

#define TINY51_OS_GPIO_PORT_2 P2

#define GPIO_HIGH (1)
#define GPIO_LOW  (0)

void platform_timer_init_10ms(void);
void platform_delay_xms(uint16_t ms);
void platform_set_gpio_inout(uint8_t gpio_x_num, uint8_t gpio_y_num);
void platform_set_gpio_value(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t gpio_value);

#define RAM_RANGE_IDATA __idata

#define SET_REGISTER_M0_VALUE(x, y, value) \
    do { \
        switch (x) { \
            case 0: P0M0 = (P0M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 1: P1M0 = (P1M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 2: P2M0 = (P2M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 3: P3M0 = (P3M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 4: P4M0 = (P4M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 5: P5M0 = (P5M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 6: P6M0 = (P6M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 7: P7M0 = (P7M0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
        } \
    } while (0)

#define SET_REGISTER_M1_VALUE(x, y, value) \
    do { \
        switch (x) { \
            case 0: P0M1 = (P0M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 1: P1M1 = (P1M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 2: P2M1 = (P2M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 3: P3M1 = (P3M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 4: P4M1 = (P4M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 5: P5M1 = (P5M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 6: P6M1 = (P6M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 7: P7M1 = (P7M1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
        } \
    } while (0)
#define SET_GPIO_OUTPUT_VALUE(x, y, value) \
    do { \
        switch (x) { \
            case 0: P0 = (P0 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 1: P1 = (P1 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 2: P2 = (P2 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 3: P3 = (P3 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 4: P4 = (P4 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 5: P5 = (P5 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 6: P6 = (P6 & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 7: P7 = (P7 & ~(1 << y)) | ((value << y) & 0xFF); break; \
        } \
    } while (0)
#endif //__PLATFORM_HEAD_H