/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "../chip_platform/platform_head.h"
#include "uart.h"

void uart_init()
{
  SCON = 0x50;
  T2L = 0xe8;                                 //65536-11059200/115200/4=0FFE8H
  T2H = 0xff;
  AUXR = 0x15;                                //启动定时器
  ES = 0;                                     //使能串口中断
  EA = 1;
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

extern char putchar(char c)  //printf函数会调用putchar()
{
  uart_write(c);
  return c;
}