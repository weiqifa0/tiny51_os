/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2024
*/
#include "gpio_i2c_interface.h"
void i2c_interface_init()
{
  P_SW2 = 0x80;
  I2CCFG = 0xe0;
  I2CMSST = 0x00;
  platform_set_gpio_mode(1, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(1, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
}

void i2c_wait()
{
  while (!(I2CMSST & 0x40));
  I2CMSST &= ~0x40;
}

void i2c_start()
{
  I2CMSCR = 0x01;
  i2c_wait();
}

void i2c_write_byte(char dat)
{
  I2CTXD = dat;
  I2CMSCR = 0x02;
  i2c_wait();
}

void i2c_receive_device_ack()
{
  I2CMSCR = 0x03;
  i2c_wait();
}

char i2c_read_byte()
{
  I2CMSCR = 0x04;
  i2c_wait();
  return I2CRXD;
}

void SendACK()
{
  I2CMSST = 0x00;
  I2CMSCR = 0x05;
  i2c_wait();
}

void i2c_host_send_no_ack()
{
  I2CMSST = 0x01;
  I2CMSCR = 0x05;
  i2c_wait();
}

void i2c_stop()
{
  I2CMSCR = 0x06;
  i2c_wait();
}