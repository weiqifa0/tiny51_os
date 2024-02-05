/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "../chip_platform/platform_head.h"
#include "uart.h"

/*
 * 115200
 */
void uart_init()
{
  SCON = 0x50;
  T2L = 0xe8;
  T2H = 0xff;
  AUXR = 0x15; // timer open
  ES = 0; // uart irq open
  EA = 1;
  TI = 1;
}

void uart_write(char encode)
{
  SBUF = encode;
  while(TI == 0);
  TI = 0;
}

void uart_write_str(char * string)
{
  while(*string != '\0') 
    uart_write(*string++);
}

char putchar(char c)
{
  uart_write(c);
  return c;
}