/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __TASK_SCHEDULING_H
#define __TASK_SCHEDULING_H

#include "../chip_platform/platform_head.h"

#define MAX_TASKS 2       //任务槽个数.必须和实际任务数一至
#define MAX_TASK_DEP 12   //最大栈深.最低不得少于2个,保守值为12.

extern unsigned char __idata task_stack[MAX_TASKS][MAX_TASK_DEP];
extern unsigned char __idata task_sp[MAX_TASKS];
extern unsigned char task_id;

// 从指定的任务开始运行任务调度.调用该宏后,将永不返回.
#define os_start(tid) {task_id = tid,SP = task_sp[tid];return;}

void tiny51_task_scheduling(void);
void task_load(unsigned int fn, unsigned char tid);

#endif //__MACHINE_CONFIG_H