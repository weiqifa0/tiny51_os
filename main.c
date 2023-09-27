/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"


/****小小调度器开始**********************************************/
#define MAXTASKS 2
static unsigned char timers[MAXTASKS];
unsigned char currdt;
#define _SS static unsigned char _lc; switch(_lc){default:
#define _EE ;}; _lc=0; return 255;
#define WaitX(tickets) do {_lc=__LINE__+((__LINE__%256)==0); return tickets ;} while(0); case __LINE__+((__LINE__%256)==0):
#define RunTask(TaskName,TaskID) do { if (timers[TaskID]==0) timers[TaskID]=TaskName(); } while(0);

#define CallSub(SubTaskName) do { _lc=__LINE__+((__LINE__%256)==0); return 0; case __LINE__+((__LINE__%256)==0): currdt=SubTaskName(); if(currdt!=255) return currdt;} while(0);
#define UpdateTimers() unsigned char i; for(i=MAXTASKS;i>0 ;i--) {if((timers[i-1]!=0)&&(timers[i-1]!=255)) timers[i-1]--;}

#define SEM unsigned int
//初始化信号量
#define InitSem(sem) sem=0;
//等待信号量
#define WaitSem(sem) do{ sem=1; WaitX(0); if (sem>0) return 1;} while(0);
//等待信号量或定时器溢出， 定时器tickets 最大为0xFFFE
#define WaitSemX(sem,tickets) do { sem=tickets+1; WaitX(0); if(sem>1){ sem--; return 1;} } while(0);
//发送信号量
#define SendSem(sem) do {sem=0;} while(0);

/*****小小调度器结束*******************************************************/

#define LED1 P2_1
#define LED2 P2_1

void InitT0()
{
  TMOD = 0x21;
  IE |= 0x82;  // 12t
  TL0=0Xff;
  TH0=0XDB;//22M---b7;
  TR0 = 1;
}

void INTT0(void) __interrupt (1) __using (1)
{
  UpdateTimers();
  TL0=0Xff;//10ms 重装
  TH0=0XDB;//b7;   
}


int task1() {
_SS
  while(1) {
    WaitX(50);
    LED1 = !LED1;
  }
_EE
}

int task2() {
_SS
  while(1) {
    WaitX(100);
    LED2=!LED2;
  }
_EE
}

void main()
{
  InitT0();
  while(1) {
    RunTask(task1, 0);
    RunTask(task2, 1);
  }
}


