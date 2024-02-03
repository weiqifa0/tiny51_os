/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2024
*/
#include "gpio_i2c_interface.h"

void i2c_gpio_init(void)
{
  platform_set_gpio_mode(1, 4, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
  platform_set_gpio_mode(1, 5, GPIO_GENERAL_PURPOSE_INPUT_OUTPUT );
}

void i2c_start(void)
{
   I2C_SDA=1;
   platform_delay_xus(1);
   I2C_SCL=1;
   platform_delay_xus(5);

   I2C_SDA=0;
   platform_delay_xus(5);

   I2C_SCL=0;
   platform_delay_xus(2);
}

void i2c_stop(void)
{
   I2C_SDA=0;
   platform_delay_xus(1);
   I2C_SCL=1;
   platform_delay_xus(5);

   I2C_SDA=1;
   platform_delay_xus(4);
}


int8_t i2c_write_byte(uint8_t dat)
{
  uint8_t i;
  int8_t answer_ack;

  for (i = 0; i < 8; i++) {
    if(dat & 0x80) {
      I2C_SDA = 1;
    } else{
      I2C_SDA = 0;
    }
    dat <<= 1;
    platform_delay_xus(1);
    I2C_SCL=1;

    platform_delay_xus(5);

    I2C_SCL=0;
  }

  platform_delay_xus(2);
  I2C_SDA=1;
  platform_delay_xus(2);
  I2C_SCL=1;
  platform_delay_xus(3);
  if(I2C_SDA == 1) {
    answer_ack = -1; /*NO ACK*/
  } else{
    answer_ack = 1;
  }
  I2C_SCL=0;
  platform_delay_xus(2);
  return answer_ack;
}


uint8_t i2c_read_byte(void)
{
  uint8_t val;
  uint8_t i;

  val=0;
  I2C_SDA = 1;
  for (i = 0; i < 8; i++) {
    platform_delay_xus(1);
    I2C_SCL = 0;
    platform_delay_xus(5);
    I2C_SCL = 1;
    platform_delay_xus(3);

    val = val << 1;
    if(I2C_SDA == 1) {
      val = val + 1;
    }

    platform_delay_xus(2);
  }
  I2C_SCL = 0;
  platform_delay_xus(2);
  return(val);
}

void i2c_answer_ack(uint8_t answer_to_device)
{
   if(answer_to_device == 0) {
     I2C_SDA = 0;
   } else {
     I2C_SDA = 1;
   }
   platform_delay_xus(3);
   I2C_SCL=1;

   platform_delay_xus(5);

   I2C_SCL=0;
   platform_delay_xus(2);
}
