/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "uart.h"

void uart_init(void)
{
  TMOD=0x21;		   //用定时器设置串口波特率	   9600
  TH1=0xfd;
  TL1=0xfd;
  TR1=1;
  REN=1;          //串口初始化
  SM0=0;
  SM1=1;
  EA=1;           //开启总中断
  ES=1;
}

void uart_write(char data)
{
  ES = 0;
  SBUF = data;
  while(!TI);
  TI = 0;
  ES = 1;
}