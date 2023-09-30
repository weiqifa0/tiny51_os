/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

task_scheduling_core_stu RAM_RANGE_IDATA task_scheduling_core_stu_t;

void tiny51_task_scheduling(void)
{
  task_scheduling_core_stu_t.task_sp[task_scheduling_core_stu_t.current_runing_pid].task_obj_address = SP;
  if (++task_scheduling_core_stu_t.current_runing_pid >= task_scheduling_core_stu_t.register_task_count)
    task_scheduling_core_stu_t.current_runing_pid = 0;
  SP = task_scheduling_core_stu_t.task_sp[task_scheduling_core_stu_t.current_runing_pid].task_obj_address;
}

void tiny51_init_task_scheduling(void)
{
  memset(&task_scheduling_core_stu_t, 0, sizeof(task_scheduling_core_stu_t));
}

void tiny51_register_task_scheduling(uint16_t task_address, uint8_t sleep_ms)
{
  int offset = task_scheduling_core_stu_t.register_task_count;
  task_scheduling_core_stu_t.task_sp[offset].task_obj_address = (uint8_t)(task_scheduling_core_stu_t.task_stack[offset] + 1);
  task_scheduling_core_stu_t.task_sp[offset].task_sleep_ms = sleep_ms;
  task_scheduling_core_stu_t.task_stack[offset][0] = (uint8_t)(task_address & 0xFF);
  task_scheduling_core_stu_t.task_stack[offset][1] = (uint8_t)(task_address >> 8);
  task_scheduling_core_stu_t.register_task_count++;
}

void tiny51_start_task_scheduling(uint8_t pid)
{
  task_scheduling_core_stu_t.current_runing_pid = pid;
  SP = task_scheduling_core_stu_t.task_sp[pid].task_obj_address;
  tiny51_run_task_in_stack();
}

inline void tiny51_run_task_in_stack(void)
{
  // when call RET, the cpu will run the address in the SP
  __asm__("RET");
}