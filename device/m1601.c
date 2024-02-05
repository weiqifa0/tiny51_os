/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "m1601.h"

void m1601_init(void)
{
  platform_set_gpio_mode(1, 1, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  M1601Z_DQ_PIN = 1;
  platform_delay_xus(500);
  M1601Z_DQ_PIN = 0;
}

void m1601_reset_cmd(void)
{
  M1601Z_DQ_PIN = 0;
  platform_delay_xus(480);
  M1601Z_DQ_PIN = 1;
}

BOOL m1601_presence_get(void)
{
  BOOL dq;
  platform_delay_xus(70);
  dq = M1601Z_DQ_PIN;
  platform_delay_xus(410);
  return dq;
}

BOOL m1601_presence_reset(void)
{
  BOOL dq;
  M1601Z_DQ_PIN = 0;
  platform_delay_xus(480);
  M1601Z_DQ_PIN = 1;
  platform_delay_xus(70);
  dq = M1601Z_DQ_PIN;
  platform_delay_xus(410);
  return dq;
}

void m1601_write_bit(BOOL high)
{
  if (high) {
    M1601Z_DQ_PIN = 0;
    platform_delay_xus(2);
    M1601Z_DQ_PIN = 1;
    platform_delay_xus(68);
  } else {
    M1601Z_DQ_PIN = 0;
    platform_delay_xus(60);
    M1601Z_DQ_PIN = 1;
    platform_delay_xus(10);
  }
}

BOOL m1601_read_bit(void)
{
  BOOL dq_bit;
  M1601Z_DQ_PIN = 0;
  platform_delay_xus(2);
  M1601Z_DQ_PIN = 1;
  platform_delay_xus(10);
  dq_bit = M1601Z_DQ_PIN;
  platform_delay_xus(58);

  return dq_bit;
}

void m1601_write_byte(uint8_t cmd)
{
  uint8_t i;
  for (i = 0; i < 8; i++) {
    m1601_write_bit(cmd & 0x01);
    cmd >>= 1;
  }
}

uint8_t m1601_read_byte(void)
{
  uint8_t i;
  uint8_t dat;
  for (i = 0; i < 8; i++) {
    dat >>= 1;
    if (m1601_read_bit()) {
      dat |= 0x80;
    }
  }

  return dat;
}

float read_temp_from_m1601(void)
{
  uint8_t scr[8];
  int i;
  uint16_t temp_u16;
  float f_temp;

  m1601_presence_reset();
  m1601_write_byte(0xCC); 
  m1601_write_byte(0x44);

  platform_delay_xms(15);

  m1601_presence_reset();
  m1601_write_byte(0xCC);
  m1601_write_byte(0xbe);
  for (i = 0; i < 8; i++) {
    scr[i] = m1601_read_byte();
  }
  
  temp_u16 = scr[1]<<8 | scr[0];

  f_temp = ((short)temp_u16)/256.0+40.0;

  return (f_temp);
}