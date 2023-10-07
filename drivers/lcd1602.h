/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#ifndef _LCD1602_H
#define _LCD1602_H

#include "../chip_platform/platform_head.h"

#define LCD1602_DB TINY51_OS_GPIO_PORT_2
#define LCD_RES TINY51_OS_GPIO0_7
#define LCD_EN  TINY51_OS_GPIO0_5
#define LCD_RW  TINY51_OS_GPIO0_6

#define SET_LCD1602_RES_LOW() (LCD_RES = 0)
#define SET_LCD1602_RES_HIGHT() (LCD_RES = 1)

#define SET_LCD1602_EN_LOW() (LCD_EN = 0)
#define SET_LCD1602_EN_HIGHT() (LCD_EN = 1)

#define SET_LCD1602_RW_LOW() (LCD_RW = 0)
#define SET_LCD1602_RW_HIGHT() (LCD_RW = 1)

bool lcd1602_busy_state(void);
void lcd1602_write_cmd(uint8_t cmd);
void lcd1602_position_x_y(uint8_t positon);
void lcd1602_write_data(uint8_t data);
void lcd1602_init(void);
void lcd1602_write_string(uint8_t x,uint8_t y,uint8_t *str);

#endif //_LCD1602_H