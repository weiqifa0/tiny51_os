/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "task_scheduling_core.h"

unsigned char __idata task_stack[MAX_TASKS][MAX_TASK_DEP];
unsigned char __idata task_sp[MAX_TASKS];
unsigned char task_id;

// 任务切换函数(任务调度器)
void tiny51_task_scheduling(void)
{
  task_sp[task_id] = SP;
  if(++task_id == MAX_TASKS)
    task_id = 0;
  SP = task_sp[task_id];
}

// 任务装入函数.将指定的函数(参数1)装入指定(参数2)的任务槽中.如果该槽中原来就有任务,则原任务丢失,但系统本身不会发生错误.
void task_load(unsigned int fn, unsigned char tid)
{
  task_sp[tid] = (unsigned char __idata)(task_stack[tid] + 1);
  task_stack[tid][0] = (unsigned int)fn & 0xff;
  task_stack[tid][1] = (unsigned int)fn >> 8;
}