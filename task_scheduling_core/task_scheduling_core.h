/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __TASK_SCHEDULING_CORE_H
#define __TASK_SCHEDULING_CORE_H

#include <string.h>

#include "../chip_platform/platform_head.h"


#define TASK_STACK_SIZE	2
#define TASK_MAX_NUM	8
#define TASK_IDLE_NUM	(0)
#define TASK_VALID_START_ID (TASK_IDLE_NUM + 1)
#define TASK_VALID_END_ID	(TASK_MAX_NUM - 1)

//任务状态定义
enum task_status {
  TINY51_OS_STATUS_RUNING = 0,
  TINY51_OS_STATUS_READY = 1,
  TINY51_OS_STATUS_DELAY = 2
};

//系统管理信息结构体
typedef struct scheduling_core_st {
  uint8_t current_task_id;
  uint8_t task_num;
} scheduling_core;

typedef struct task_obj_st {
  uint8_t addr_tab[TASK_STACK_SIZE];//本任务的栈空间
  uint8_t ACC;
  uint8_t B;
  uint8_t PSW;
  uint8_t DPL;
  uint8_t DPH;
  uint8_t ar0;
  uint8_t ar1;
  uint8_t ar2;
  uint8_t ar3;
  uint8_t ar4;
  uint8_t ar5;
  uint8_t ar6;
  uint8_t ar7;
  uint8_t stack_top;//本任务的栈顶空间
  uint8_t status;//任务状态
  uint8_t task_id;//本任务的任务号
  uint16_t delay_ms; //剩余时间片时间
} task_obj;


extern scheduling_core RAM_RANGE_IDATA scheduling_core_t;
extern task_obj RAM_RANGE_IDATA tiny51_task[TASK_MAX_NUM];

uint8_t tiny51_get_current_task(void);
uint8_t tiny51_get_next_task(void);
void tiny51_init_task_scheduling(void);
void tiny51_register_task_scheduling(uint8_t task_id, void (*task_fun_address)(void));
void tiny51_task_start(uint8_t task_id);
void tiny51_task_scheduling(void);
void tiny51_task_delay(uint16_t delay_ms);
void tiny51_set_current_task(uint8_t current_task);

#endif //__TASK_SCHEDULING_CORE_H