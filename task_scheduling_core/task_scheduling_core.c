/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

scheduling_core RAM_RANGE_IDATA scheduling_core_t;

void tiny51_task_scheduling(void)
{
#if TASK_SCHEDULING_BY_SP
  scheduling_core_t.task_sp[scheduling_core_t.current_runing_pid].task_obj_address = SP;
  if (++scheduling_core_t.current_runing_pid >= scheduling_core_t.register_task_count)
    scheduling_core_t.current_runing_pid = 0;
  SP = scheduling_core_t.task_sp[scheduling_core_t.current_runing_pid].task_obj_address;
#else
  int i;

  for (i = 0; i < scheduling_core_t.register_task_count; i++) {
    if (scheduling_core_t.task_sp[i].heartbeat_count_per_1ms >= scheduling_core_t.task_sp[i].task_sleep_ms) {
        scheduling_core_t.current_runing_pid = i;
        scheduling_core_t.task_sp[i].heartbeat_count_per_1ms = 0;
        tiny51_run_task_in_stack(scheduling_core_t.task_sp[i].task_address);
      }
  }
#endif
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
#if TASK_SCHEDULING_BY_SP
  scheduling_core_t.task_sp[offset].task_obj_address = (uint8_t)(scheduling_core_t.task_stack[offset] + 1);
  scheduling_core_t.task_stack[offset][0] = (uint8_t)(task_address & 0xFF);
  scheduling_core_t.task_stack[offset][1] = (uint8_t)(task_address >> 8);
#endif
  scheduling_core_t.register_task_count++;
}

void tiny51_start_task_scheduling(uint8_t pid)
{
  scheduling_core_t.current_runing_pid = pid;
#if TASK_SCHEDULING_BY_SP
  tiny51_run_task_in_stack(scheduling_core_t.task_sp[pid].task_obj_address);
#endif
}

inline void tiny51_run_task_in_stack(uint16_t ready_to_run_address)
{

#if TASK_SCHEDULING_BY_SP
  // set the function address to SP register
  SP = ready_to_run_address;
  // when call RET, the cpu will run the address in the SP
  __asm__("RET");
#else
  callback_func* p_run = (callback_func*)ready_to_run_address;
  p_run();
#endif
  PLATFORM_UNUSED(ready_to_run_address);
}