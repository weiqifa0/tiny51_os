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
void i2c_start();

void i2c_write_byte(char dat);

void i2c_receive_device_ack();

char i2c_read_byte();

void SendACK();

void i2c_host_send_no_ack();
void i2c_stop();



