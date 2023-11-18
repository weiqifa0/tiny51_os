/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "lcd1602.h"

bool lcd1602_busy_state(void)
{
  bool busy_state;
  SET_LCD1602_RES_LOW();
  SET_LCD1602_RW_HIGHT();
  SET_LCD1602_EN_HIGHT();
  PLATFORM_NOP_4();
  busy_state = (bool)(LCD1602_DB & 0x80);
  SET_LCD1602_EN_LOW();
  return busy_state;
}

void lcd1602_write_cmd(uint8_t cmd)
{
  while (lcd1602_busy_state());
  SET_LCD1602_RES_LOW();
  SET_LCD1602_RW_LOW();
  SET_LCD1602_EN_LOW();
  PLATFORM_NOP_2();
  LCD1602_DB = cmd;
  PLATFORM_NOP_4();
  SET_LCD1602_EN_HIGHT();
  PLATFORM_NOP_4();
  SET_LCD1602_EN_LOW();
}

void lcd1602_position_x_y(uint8_t positon)
{
  lcd1602_write_cmd(positon| 0x80);
}

void lcd1602_write_data(uint8_t data)
{
  while (lcd1602_busy_state());
  SET_LCD1602_RES_HIGHT();
  SET_LCD1602_RW_LOW();
  SET_LCD1602_EN_LOW();
  PLATFORM_NOP_2();
  LCD1602_DB = data;
  PLATFORM_NOP_4();
  SET_LCD1602_EN_HIGHT();
  PLATFORM_NOP_4();
  SET_LCD1602_EN_LOW();
}

void lcd1602_write_char(uint8_t x, uint8_t y, uint8_t data)
{
  lcd1602_write_cmd(0x80);
  if (y == 0) {
    lcd1602_write_cmd(0x80 + x);
  } else {
    lcd1602_write_cmd(0x80 + 0x40 + x);
  }
  lcd1602_write_data(data);
}

void lcd1602_write_string(uint8_t x, uint8_t y, uint8_t* str)
{
  lcd1602_write_cmd(0x80);
  if(y == LCD1602_FIRST_ROW) {
    lcd1602_write_cmd(0x80 + x);
  } else {
    lcd1602_write_cmd(0xC0 + x);
  }

  while (*str != '\0') {
    lcd1602_write_data(*str);
    str++;
  }
}

void lcd1602_init(void)
{
  lcd1602_write_cmd(0x38);
  platform_delay_xms(1);
  lcd1602_write_cmd(0x0c);
  platform_delay_xms(1);
  lcd1602_write_cmd(0x06);
  platform_delay_xms(1);
  lcd1602_write_cmd(0x01);
  platform_delay_xms(1);
  platform_delay_xms(10);
}