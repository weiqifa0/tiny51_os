/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __TASK_SCHEDULING_H
#define __TASK_SCHEDULING_H

#include "../chip_platform/platform_head.h"

#define MAX_TASK_COUNT 5
#define MAX_TASK_DEEP_SIZE 12

extern uint8_t RAM_RANGE_IDATA task_stack[MAX_TASK_COUNT][MAX_TASK_DEEP_SIZE];
extern uint8_t RAM_RANGE_IDATA task_sp[MAX_TASK_COUNT];
extern uint8_t current_task_pid;

// 从指定的任务开始运行任务调度.调用该宏后,将永不返回.
#define start_task_scheduling(pid) {current_task_pid = pid, SP = task_sp[pid]; return;}

void tiny51_task_scheduling(void);
void register_task_scheduling(uint16_t ftask_addressn, uint8_t tid);

#endif //__MACHINE_CONFIG_H