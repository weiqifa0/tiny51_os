/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "uart.h"
#include "led.h"
#include "../chip_platform/platform_head.h"

uint8_t uart_send_busy = 0;

void uart_init(unsigned int baudrate)
{
  SCON = 0x50; // 设置串口工作方式为1
  T2L = 0xE8;
  T2H = 0xFF;
  AUXR = 0x15;
  ES = 1;
  TR1 = 1;
  EA = 1;
}

void uart_write(char encode)
{
  SBUF = encode;
  while (TI);
}

void uart_write_str(char* str)
{
  while (*str)
  {
    uart_write(*str++);
  }
}

void uart_clear_write_busy(void)
{
  uart_send_busy = 0;
}

// void uartISR(void) __interrupt (4)
// {
//   char tmp;
//   EA = 0;
//   set_led_num(8, FALSE);
//   if (TI)
//   {
//     TI = 0;
//   }
//   if (RI)
//   {
//     tmp = SBUF;
//     RI = 0;
//     SBUF = tmp;
//   }
//   platform_delay_xms(200);
//   set_led_num(8, TRUE);
//   EA = 1;
// }