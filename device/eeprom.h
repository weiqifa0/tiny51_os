/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "../driver/gpio_i2c_interface.h"

#define EEPROM_I2C_ADDRESS (0xA0)

void eeprom_init(void);
int8_t eeprom_write_to_address(uint8_t dat, uint16_t address);
uint8_t eeprom_read_from_address(uint16_t address);