/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __PLATFORM_TYPE_H
#define __PLATFORM_TYPE_H

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef __bit bool;

#define NULL (void *)0
#define TRUE (1)
#define FALSE (0)

#define PLATFORM_UNUSED(X) (X = X)

#define PLATFORM_NOP_1()  __asm__("nop");
#define PLATFORM_NOP_2()  PLATFORM_NOP_1();__asm__("nop");
#define PLATFORM_NOP_3()  PLATFORM_NOP_2();__asm__("nop");
#define PLATFORM_NOP_4()  PLATFORM_NOP_3();__asm__("nop");
#define PLATFORM_NOP_5()  PLATFORM_NOP_4();__asm__("nop");
#define PLATFORM_NOP_6()  PLATFORM_NOP_5();__asm__("nop");
#define PLATFORM_NOP_7()  PLATFORM_NOP_6();__asm__("nop");
#define PLATFORM_NOP_8()  PLATFORM_NOP_7();__asm__("nop");
#define PLATFORM_NOP_9()  PLATFORM_NOP_8();__asm__("nop");
#define PLATFORM_NOP_10()  PLATFORM_NOP_9();__asm__("nop");
#define PLATFORM_NOP_11()  PLATFORM_NOP_10();__asm__("nop");
#define PLATFORM_NOP_12()  PLATFORM_NOP_11();__asm__("nop");
#define PLATFORM_NOP_13()  PLATFORM_NOP_12();__asm__("nop");
#define PLATFORM_NOP_14()  PLATFORM_NOP_13();__asm__("nop");
#define PLATFORM_NOP_15()  PLATFORM_NOP_14();__asm__("nop");
#define PLATFORM_NOP_16()  PLATFORM_NOP_15();__asm__("nop");
#define PLATFORM_NOP_17()  PLATFORM_NOP_16();__asm__("nop");
#define PLATFORM_NOP_18()  PLATFORM_NOP_17();__asm__("nop");
#define PLATFORM_NOP_19()  PLATFORM_NOP_18();__asm__("nop");
#define PLATFORM_NOP_20()  PLATFORM_NOP_19();__asm__("nop");
#define PLATFORM_NOP_21()  PLATFORM_NOP_20();__asm__("nop");
#define PLATFORM_NOP_22()  PLATFORM_NOP_21();__asm__("nop");
#define PLATFORM_NOP_23()  PLATFORM_NOP_22();__asm__("nop");
#define PLATFORM_NOP_24()  PLATFORM_NOP_23();__asm__("nop");
#define PLATFORM_NOP_25()  PLATFORM_NOP_24();__asm__("nop");
#define PLATFORM_NOP_26()  PLATFORM_NOP_25();__asm__("nop");
#define PLATFORM_NOP_27()  PLATFORM_NOP_26();__asm__("nop");
#define PLATFORM_NOP_28()  PLATFORM_NOP_27();__asm__("nop");
#define PLATFORM_NOP_29()  PLATFORM_NOP_28();__asm__("nop");
#define PLATFORM_NOP_30()  PLATFORM_NOP_29();__asm__("nop");
#define PLATFORM_NOP_31()  PLATFORM_NOP_30();__asm__("nop");
#define PLATFORM_NOP_32()  PLATFORM_NOP_31();__asm__("nop");

#define PLATFORM_NOP(N)   PLATFORM_NOP_##N()

#define PLATFORM_OPEN_IRQ(x) EA = x

#endif //__PLATFORM_TYPE_H