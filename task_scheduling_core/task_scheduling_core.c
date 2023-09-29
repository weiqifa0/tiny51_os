/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

uint8_t RAM_RANGE_IDATA task_stack[MAX_TASK_COUNT][MAX_TASK_DEEP_SIZE];
uint8_t RAM_RANGE_IDATA task_sp[MAX_TASK_COUNT];
uint8_t current_task_pid;
uint8_t RAM_RANGE_IDATA task_count = 0;

void tiny51_task_scheduling(void)
{
  task_sp[current_task_pid] = SP;
  if(++current_task_pid >= task_count)
    current_task_pid = 0;
  SP = task_sp[current_task_pid];
}

void register_task_scheduling(uint16_t task_address, uint8_t tid)
{
  task_sp[task_count] = (uint8_t RAM_RANGE_IDATA)(task_stack[task_count] + 1);
  task_stack[task_count][0] = (unsigned int)task_address & 0xff;
  task_stack[task_count][1] = (unsigned int)task_address >> 8;
  task_count++;
}