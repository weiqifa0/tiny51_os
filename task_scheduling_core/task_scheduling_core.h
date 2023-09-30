/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __TASK_SCHEDULING_H
#define __TASK_SCHEDULING_H

#include <string.h>

#include "../chip_platform/platform_head.h"

#define MAX_TASK_COUNT 12
#define MAX_TASK_ADDRESS_SIZE_BYTES 2
#define TASK_SCHEDULING_BY_SP 0

typedef void callback_func(void);
typedef struct task_obj_st
{

  uint16_t task_address;
#if TASK_SCHEDULING_BY_SP
  uint8_t task_obj_address;
#endif
  uint16_t task_sleep_ms;
  uint16_t heartbeat_count;
} task_obj;
typedef struct scheduling_core_st
{
#if TASK_SCHEDULING_BY_SP
  uint8_t task_stack[MAX_TASK_COUNT][MAX_TASK_ADDRESS_SIZE_BYTES];
#endif
  task_obj task_sp[MAX_TASK_COUNT];
  uint8_t register_task_count;
  uint8_t current_runing_pid;
} scheduling_core;

void tiny51_task_scheduling(void);
void tiny51_register_task_scheduling(uint16_t ftask_addressn, uint16_t sleep_ms);
void tiny51_start_task_scheduling(uint8_t pid);
inline void tiny51_run_task_in_stack(uint8_t ready_to_run_address);
inline void tiny51_init_task_scheduling(void);

#endif //__MACHINE_CONFIG_H