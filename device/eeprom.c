/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#include "eeprom.h"
void eeprom_init(void)
{

}

int8_t eeprom_write_to_address(uint8_t dat, uint16_t address)
{
  int8_t ret = 0;
  i2c_start();
  ret |= i2c_write_byte(EEPROM_I2C_ADDRESS);
  //ret |= i2c_write_byte((uint8_t)(address >> 8));
  ret |= i2c_write_byte((uint8_t)(address));
  ret |= i2c_write_byte(dat);
  i2c_stop();
  return ret;
}

uint8_t eeprom_read_from_address(uint16_t address)
{
  uint8_t dat;
  i2c_start();
  i2c_write_byte(EEPROM_I2C_ADDRESS);
  //i2c_write_byte((uint8_t)(address >> 8));
  i2c_write_byte((uint8_t)(address));
  i2c_start();
  i2c_write_byte(EEPROM_I2C_ADDRESS + 1);
  dat = i2c_read_byte();
  i2c_answer_ack(0);
  i2c_stop();
  return dat;
}