/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __PLATFORM_HEAD_H__
#define __PLATFORM_HEAD_H__

#define COMPLILE_SDCC (0)
#define COMPLILE_KEIL (1)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

#if COMPLILE_SDCC
  #include "stc8h8k64u_sdcc.h"
  typedef __bit bool;
  #define __NOP__() __asm__("nop")
  #define RAM_RANGE_IDATA __idata
#elif COMPLILE_KEIL
  #define bool sbit
  #define __NOP__() _nop_()
  #include "stc8h8k64u_keil.h"
  #include "intrins.h"
  #define RAM_RANGE_IDATA idata
#endif

#define NULL (void *)0
#define TRUE (1)
#define FALSE (0)

#define PLATFORM_UNUSED(X) (X = X)

#define CPU_MCLK 110592 //HZ

#if COMPLILE_SDCC
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
#elif COMPLILE_KEIL

#endif

#define TINY51_OS_GPIO_PORT_2 P2

#define GPIO_HIGH (1)
#define GPIO_LOW  (0)


enum TINY51_OS_GPIO_MODE {
  GPIO_GENERAL_PURPOSE_INPUT_OUTPUT ,
  GPIO_PUSH_PULL_OUTPUT,
  GPIO_HIGH_INPEDANCE_INPUT,
  GPIO_OPEN_COLLECTOR_OUTPUT
};

enum TINY51_OS_GPIO_DRIVER {
  GPIO_HIGH_DRIVER = 0,
  GPIO_LOW_DRIVER = 1
};

void platform_timer_init_10ms(void);
void platform_delay_xms(uint16_t ms);
void platform_set_gpio_mode(uint8_t gpio_x_num, uint8_t gpio_y_num, enum TINY51_OS_GPIO_MODE mode);
void platform_set_gpio_value(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t gpio_value);
void platform_set_gpio_pull_up_resister(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t value);
void platform_set_gpio_driver_capability(uint8_t gpio_x_num, uint8_t gpio_y_num, uint8_t value);

#define SET_GPIO_DRIVE_CAPABILITY(x, y, value) \
    do { \
        switch (x) { \
            case 0: P0DR = (P0DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 1: P1DR = (P1DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 2: P2DR = (P2DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 3: P3DR = (P3DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 4: P4DR = (P4DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 5: P5DR = (P5DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 6: P6DR = (P6DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 7: P7DR = (P7DR & ~(1 << y)) | ((value << y) & 0xFF); break; \
        } \
    } while (0)

#define SET_REGISTER_PU_VALUE(x, y, value) \
    do { \
        switch (x) { \
            case 0: P0PU = (P0PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 1: P1PU = (P1PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 2: P2PU = (P2PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 3: P3PU = (P3PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 4: P4PU = (P4PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 5: P5PU = (P5PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 6: P6PU = (P6PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
            case 7: P7PU = (P7PU & ~(1 << y)) | ((value << y) & 0xFF); break; \
        } \
    } while (0)

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

#define PLATFORM_NOP_1()  __NOP__()
#define PLATFORM_NOP_2()  PLATFORM_NOP_1();__NOP__()
#define PLATFORM_NOP_3()  PLATFORM_NOP_2();__NOP__()
#define PLATFORM_NOP_4()  PLATFORM_NOP_3();__NOP__()
#define PLATFORM_NOP_5()  PLATFORM_NOP_4();__NOP__()
#define PLATFORM_NOP_6()  PLATFORM_NOP_5();__NOP__()
#define PLATFORM_NOP_7()  PLATFORM_NOP_6();__NOP__()
#define PLATFORM_NOP_8()  PLATFORM_NOP_7();__NOP__()
#define PLATFORM_NOP_9()  PLATFORM_NOP_8();__NOP__()
#define PLATFORM_NOP_10()  PLATFORM_NOP_9();__NOP__()
#define PLATFORM_NOP_11()  PLATFORM_NOP_10();__NOP__()
#define PLATFORM_NOP_12()  PLATFORM_NOP_11();__NOP__()
#define PLATFORM_NOP_13()  PLATFORM_NOP_12();__NOP__()
#define PLATFORM_NOP_14()  PLATFORM_NOP_13();__NOP__()
#define PLATFORM_NOP_15()  PLATFORM_NOP_14();__NOP__()
#define PLATFORM_NOP_16()  PLATFORM_NOP_15();__NOP__()
#define PLATFORM_NOP_17()  PLATFORM_NOP_16();__NOP__()
#define PLATFORM_NOP_18()  PLATFORM_NOP_17();__NOP__()
#define PLATFORM_NOP_19()  PLATFORM_NOP_18();__NOP__()
#define PLATFORM_NOP_20()  PLATFORM_NOP_19();__NOP__()
#define PLATFORM_NOP_21()  PLATFORM_NOP_20();__NOP__()
#define PLATFORM_NOP_22()  PLATFORM_NOP_21();__NOP__()
#define PLATFORM_NOP_23()  PLATFORM_NOP_22();__NOP__()
#define PLATFORM_NOP_24()  PLATFORM_NOP_23();__NOP__()
#define PLATFORM_NOP_25()  PLATFORM_NOP_24();__NOP__()
#define PLATFORM_NOP_26()  PLATFORM_NOP_25();__NOP__()
#define PLATFORM_NOP_27()  PLATFORM_NOP_26();__NOP__()
#define PLATFORM_NOP_28()  PLATFORM_NOP_27();__NOP__()
#define PLATFORM_NOP_29()  PLATFORM_NOP_28();__NOP__()
#define PLATFORM_NOP_30()  PLATFORM_NOP_29();__NOP__()
#define PLATFORM_NOP_31()  PLATFORM_NOP_30();__NOP__()
#define PLATFORM_NOP_32()  PLATFORM_NOP_31();__NOP__()

#define PLATFORM_NOP(N)   PLATFORM_NOP_##N()

#define PLATFORM_OPEN_IRQ(x) EA = x
#endif //__PLATFORM_HEAD_H__