/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __UART_H
#define __UART_H

#include "../chip_platform/platform_head.h"

void uart_init(unsigned int baudrate);
void uart_write(char data);
void uart_clear_write_busy(void);
void uart_write_str(char* str);
// extern void uartISR(void) __interrupt (4);
#endif
