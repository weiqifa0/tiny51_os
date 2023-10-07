/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __TASK_SCHEDULING_H
#define __TASK_SCHEDULING_H

#include <string.h>

#include "../chip_platform/platform_head.h"


#define TASK_STACK_SIZE	15
#define TASK_MAX_NUM	8
#define TASK_IDLE_NUM	(TASK_MAX_NUM - 1) 
#define TASK_VALID_NUM	(TASK_MAX_NUM - 2) 


typedef void callback_func(void);


//任务状态定义
#define RUN_STATUS		0
#define READY_STATUS	1
#define DELAY_STATUS 	2

//系统管理信息结构体
typedef struct scheduling_core_st
{
	uint8_t cur_task;
}scheduling_core;

typedef struct task_obj_st
{
	uint8_t addr_tab[TASK_STACK_SIZE];//本任务的栈空间
	uint8_t stack_top;//本任务的栈顶空间
	uint8_t status;//任务状态
	uint8_t num;//本任务的任务号
	uint16_t delayms; //剩余时间片时间
}task_obj;


extern scheduling_core RAM_RANGE_IDATA scheduling_core_t;
extern task_obj __idata tiny51_task[TASK_MAX_NUM];

void tiny51_init_task_scheduling(void);
void tiny51_register_task_scheduling(uint8_t task_num,void (*task_fun)(void));
void tiny51_task_start(uint8_t task_num);
uint8_t tiny51_get_current_task(void);
uint8_t tiny51_get_next_task(void);
void tiny51_task_scheduling(void);
void tiny51_task_delayms(uint16_t ms);

#endif //__MACHINE_CONFIG_H