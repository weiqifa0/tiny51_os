/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

scheduling_core RAM_RANGE_IDATA scheduling_core_t;
task_obj RAM_RANGE_IDATA tiny51_task[TASK_MAX_NUM];


uint8_t tiny51_get_next_task(void)
{
  uint8_t tmp_task_id = scheduling_core_t.current_task_id;
  while (1)
  {
    if (tmp_task_id < TASK_VALID_END_ID) {
      tmp_task_id += 1;
    } else {
      tmp_task_id = TASK_VALID_START_ID;
    }

    if (tmp_task_id == scheduling_core_t.current_task_id) {
      scheduling_core_t.current_task_id = TASK_IDLE_NUM;
      break;
    }

    if (tiny51_task[tmp_task_id].status == TINY51_OS_STATUS_READY) {
      scheduling_core_t.current_task_id = tmp_task_id;
      break;
    } else {
      continue;
    }
  }

  return scheduling_core_t.current_task_id;
}

uint8_t tiny51_get_current_task(void)
{
  return scheduling_core_t.current_task_id;
}

void tiny51_set_current_task(uint8_t current_task)
{
  scheduling_core_t.current_task_id = current_task;
}

// 将任务添加到系统中
void tiny51_register_task_scheduling(uint8_t task_id, void (*task_fun_address)(void))
{
  if (scheduling_core_t.task_num < TASK_MAX_NUM) {
    tiny51_task[scheduling_core_t.task_num].addr_tab[0] = (uint16_t)task_fun_address & 0xff;
    tiny51_task[scheduling_core_t.task_num].addr_tab[1] = ((uint16_t)task_fun_address >> 8) & 0xff;
    tiny51_task[scheduling_core_t.task_num].stack_top = (uint8_t)(tiny51_task[task_id].addr_tab + 15);
    tiny51_task[scheduling_core_t.task_num].delay_ms = 0;
    tiny51_task[scheduling_core_t.task_num].status = TINY51_OS_STATUS_READY;
    tiny51_task[scheduling_core_t.task_num].task_id = task_id;
    scheduling_core_t.task_num++;
  }
}

// 输出栈指针
uint8_t tiny51_get_task_sp(uint8_t task_id)
{
  return tiny51_task[task_id].stack_top;
}

void tiny51_task_schedule(void)
{
  EA = 0;

  __asm__("PUSH ACC");
  __asm__("PUSH B");
  __asm__("PUSH DPH");
  __asm__("PUSH DPL");
  __asm__("PUSH PSW");
  __asm__("PUSH ar0");
  __asm__("PUSH ar1");
  __asm__("PUSH ar2");
  __asm__("PUSH ar3");
  __asm__("PUSH ar4");
  __asm__("PUSH ar5");
  __asm__("PUSH ar6");
  __asm__("PUSH ar7");

  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_next_task()].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;

  __asm__("POP ar7");
  __asm__("POP ar6");
  __asm__("POP ar5");
  __asm__("POP ar4");
  __asm__("POP ar3");
  __asm__("POP ar2");
  __asm__("POP ar1");
  __asm__("POP ar0");
  __asm__("POP PSW");
  __asm__("POP DPL");
  __asm__("POP DPH");
  __asm__("POP B");

  EA = 1;
}

void tiny51_task_start(uint8_t task_id)
{
  tiny51_task[task_id].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_get_task_sp(task_id);
  tiny51_set_current_task(task_id);

  __asm__("POP ar7");
  __asm__("POP ar6");
  __asm__("POP ar5");
  __asm__("POP ar4");
  __asm__("POP ar3");
  __asm__("POP ar2");
  __asm__("POP ar1");
  __asm__("POP ar0");
  __asm__("POP PSW");
  __asm__("POP DPL");
  __asm__("POP DPH");
  __asm__("POP B");
  __asm__("POP ACC");
  __asm__("RET");
}

void os_task_delayms_handle(void)
{
  static uint8_t i = 0;
  for (i = 0; i < (TASK_VALID_END_ID + 1); i++) {
    if (tiny51_task[i].status == TINY51_OS_STATUS_DELAY) {
      tiny51_task[i].delay_ms--;
      if (tiny51_task[i].delay_ms == 0) {
        tiny51_task[i].status = TINY51_OS_STATUS_READY;
      }
    }
  }
}

void tiny51_task_delay(uint16_t delay_ms)
{
  EA = 0; // 关中断
  tiny51_task[scheduling_core_t.current_task_id].delay_ms = delay_ms;
  tiny51_task[scheduling_core_t.current_task_id].status = TINY51_OS_STATUS_DELAY;
  tiny51_task_schedule();
  EA = 1; // 开中断
}


void tiny51_task_idle(void)
{
  while (1)
    ;
}

void tiny51_init_task_scheduling(void)
{
  memset(&tiny51_task, 0, sizeof(tiny51_task));
  memset(&scheduling_core_t, 0, sizeof(scheduling_core_t));
  tiny51_register_task_scheduling(TASK_IDLE_NUM, tiny51_task_idle);
}


void tiny51_task_scheduling(void)
{
  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_current_task()].status = TINY51_OS_STATUS_READY;
  tiny51_task[tiny51_get_next_task()].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;
}