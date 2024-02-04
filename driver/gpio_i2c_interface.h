/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2024
*/

#include "../chip_platform/platform_head.h"

void i2c_gpio_init(void);

#if COMPLILE_SDCC
#define I2C_SDA P1_4
#define I2C_SCL P1_5
#elif COMPLILE_KEIL
#define I2C_SDA P14
#define I2C_SCL P15
#endif
void i2c_interface_init();
void Wait();
void Start();

void SendData(char dat);

void RecvACK();

char RecvData();

void SendACK();

void SendNAK();
void Stop();



