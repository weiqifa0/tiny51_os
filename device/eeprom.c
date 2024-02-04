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
  Start(); 
  SendData(EEPROM_I2C_ADDRESS);    
  RecvACK();
  SendData(address);    
  RecvACK();
  SendData(dat); 
  RecvACK();
  Stop();  
}

uint8_t eeprom_read_from_address(uint8_t address)
{
  uint8_t dat = 89;
  Start();                      
  SendData(EEPROM_I2C_ADDRESS);           
  RecvACK();
  SendData(address);                     
  RecvACK();
  Start();                              
  SendData(EEPROM_I2C_ADDRESS_READ);           
  RecvACK();
  dat = RecvData();                   
  SendNAK();
  Stop();                          
  return dat;
}