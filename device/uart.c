/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "uart.h"

uint8_t uart_send_busy = 0;

void uart_init(void)
{
  TMOD=0x21;		   //用定时器设置串口波特率	   9600
  TH1=0xfd;
  TL1=0xfd;
  TR1=1;
  REN=1;          //串口初始化
  SM0=0;
  SM1=1;
  // EA=1;           //开启总中断
  ES=1;
}

void uart_write(char data)
{
  while (uart_send_busy);
  uart_send_busy = 1;
  SBUF = data;
}

void uart_clear_write_busy(void)
{
  uart_send_busy = 0;
}