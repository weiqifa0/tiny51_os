/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "lcd1602.h"

uint8_t lcd1602_busy_state(void)
{
  uint8_t busy_state;
  SET_LCD1602_RES_LOW();
  SET_LCD1602_RW_HIGHT();
  SET_LCD1602_EN_HIGHT();
  PLATFORM_NOP_4();
  busy_state = (uint8_t)(LCD1602_DB & 0x80);
  SET_LCD1602_EN_LOW();
  return busy_state;
}

void lcd1602_write_cmd(uint8_t cmd)
{
  uint8_t c = 0;
  while (lcd1602_busy_state())
  {
    platform_delay_xms(300);
    c++;
    if (c >= 10)
    {
      return;
    }
  }
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

void lcd1602_write_data(uint8_t encode)
{
  uint8_t c = 0;
  while (lcd1602_busy_state())
  {
    platform_delay_xms(300);
    c++;
    if (c >= 10)
    {
      return;
    }
  }
  SET_LCD1602_RES_HIGHT();
  SET_LCD1602_RW_LOW();
  SET_LCD1602_EN_LOW();
  PLATFORM_NOP_2();
  LCD1602_DB = encode;
  PLATFORM_NOP_4();
  SET_LCD1602_EN_HIGHT();
  PLATFORM_NOP_4();
  SET_LCD1602_EN_LOW();
}

void lcd1602_write_char(uint8_t x, uint8_t y, uint8_t encode)
{
  lcd1602_write_cmd(0x80);
  if (y == LCD1602_FIRST_ROW) {
    lcd1602_write_cmd(0x80 + x);
  } else {
    lcd1602_write_cmd(0x80 + 0x40 + x);
  }
  lcd1602_write_data(encode);
}

void lcd1602_write_string(uint8_t x, uint8_t y, uint8_t* str)
{
  // lcd1602_write_cmd(0x80);
  // if(y == LCD1602_FIRST_ROW) {
  //   lcd1602_write_cmd(0x80 + x);
  // } else {
  //   lcd1602_write_cmd(0xC0 + x);
  // }

  while (*str != '\0') {
    lcd1602_write_char(x++, y, *str);
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

void lcd1602_gpio_init(void)
{
  // 1602 BL
  platform_set_gpio_mode(7, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_pull_up_resister(7, 4, TRUE);
  platform_set_gpio_value(7, 4, GPIO_HIGH);
  platform_set_gpio_mode(4, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_pull_up_resister(4, 1, TRUE);
  platform_set_gpio_value(4, 1, GPIO_LOW);

  // 1602 gpio init
  platform_set_gpio_mode(4, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(4, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(4, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 0, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 2, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 3, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 6, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(2, 7, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
}