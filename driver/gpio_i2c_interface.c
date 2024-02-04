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

void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;
    I2CMSCR = 0x02;
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;
    I2CMSCR = 0x05;
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;
    I2CMSCR = 0x05;
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;
    Wait();
}