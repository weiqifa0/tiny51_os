/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

scheduling_core RAM_RANGE_IDATA scheduling_core_t;

void tiny51_task_scheduling(void)
{
  int i;

  for (i = 0; i < scheduling_core_t.register_task_count; i++) {
    if (scheduling_core_t.task_sp[i].heartbeat_count_per_1ms >= scheduling_core_t.task_sp[i].task_sleep_ms) {
        scheduling_core_t.current_runing_pid = i;
        scheduling_core_t.task_sp[i].heartbeat_count_per_1ms = 0;
        tiny51_run_task_in_stack(scheduling_core_t.task_sp[i].task_address);
      }
  }
}

void tiny51_init_task_scheduling(void)
{
  memset(&scheduling_core_t, 0, sizeof(scheduling_core_t));
}

void tiny51_register_task_scheduling(uint16_t task_address, uint16_t task_sleep_ms)
{
  int offset = scheduling_core_t.register_task_count;
  scheduling_core_t.task_sp[offset].task_address = task_address;
  scheduling_core_t.task_sp[offset].task_sleep_ms = task_sleep_ms;
  scheduling_core_t.register_task_count++;
}

void tiny51_start_task_scheduling(uint8_t pid)
{
  scheduling_core_t.current_runing_pid = pid;
}

void tiny51_run_task_in_stack(uint16_t ready_to_run_address)
{
  callback_func* p_run = (callback_func*)ready_to_run_address;

  p_run();

  PLATFORM_UNUSED(ready_to_run_address);
}