/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#ifndef __M1601_H
#define __M1601_H

/*
 * http://www.mysentech.com/gjdszwdxpm1601
 */

#include "../chip_platform/platform_head.h"

#if COMPLILE_SDCC
  #define M1601Z_DQ_PIN P1_1
#elif COMPLILE_KEIL
  #define M1601Z_DQ_PIN P11
#endif

#define M1601_REG_SIZE (8)

typedef struct
{
  unsigned char T_lsb;					/*The LSB of 温度结果, RO*/
  unsigned char T_msb;					/*The MSB of 温度结果, RO*/
  unsigned char C1_lsb;					/*The LSB of 电容通道C1, RO*/
  unsigned char C1_msb;					/*The MSB of 电容通道C1, Ro*/	
  unsigned char Tha_set_lsb;		
  unsigned char Tla_set_lsb;		
  unsigned char Cfg;						/*系统配置寄存器, RW*/
  unsigned char Status;					/*系统状态寄存器, RO*/
  unsigned char crc_scr;				/*CRC for byte0-7, RO*/
} SCRATCHPAD_READ;

void m1601_init(void);
void m1601_reset_cmd(void);
void m1601_write_bit(BOOL high);
uint8_t m1601_read_byte(void);
void m1601_write_byte(uint8_t cmd);
float read_temp_from_m1601(void);
#endif // __M1601_H