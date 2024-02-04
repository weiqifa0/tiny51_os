/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#include "eeprom.h"
void eeprom_init(void)
{

}

void eeprom_write_to_address(uint8_t address, uint8_t dat)
{
  i2c_start();
  i2c_write_byte(EEPROM_I2C_ADDRESS);
  i2c_receive_device_ack();
  i2c_write_byte(address);
  i2c_receive_device_ack();
  i2c_write_byte(dat);
  i2c_receive_device_ack();
  i2c_stop();
}

uint8_t eeprom_read_from_address(uint8_t address)
{
  uint8_t dat = 89;
  i2c_start();
  i2c_write_byte(EEPROM_I2C_ADDRESS);
  i2c_receive_device_ack();
  i2c_write_byte(address);
  i2c_receive_device_ack();
  i2c_start();
  i2c_write_byte(EEPROM_I2C_ADDRESS_READ);
  i2c_receive_device_ack();
  dat = i2c_read_byte();
  i2c_host_send_no_ack();
  i2c_stop();
  return dat;
}