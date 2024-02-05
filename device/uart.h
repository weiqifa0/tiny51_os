/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include "../chip_platform/platform_head.h"

void uart_init();
void uart_write(char encode);
void uart_write_str(char * string);
extern char putchar(char c);
#endif
