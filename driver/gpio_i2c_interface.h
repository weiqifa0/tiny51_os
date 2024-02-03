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

void i2c_gpio_init(void);
void i2c_start(void);
void i2c_stop(void);
int8_t i2c_write_byte(uint8_t dat);
uint8_t i2c_read_byte(void);
void i2c_answer_ack(uint8_t answer_to_device);



