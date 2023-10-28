/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"
#include "drivers/lcd1602.h"

void task1(void); //函数1
void task2(void); //函数2
void delay(unsigned short time);//延时函数

unsigned char a;	//函数一运行的标志
unsigned char b;  //函数二运行的标志
unsigned char task1_stack[20];    //函数堆栈
unsigned char task2_stack[20];    //函数堆栈
//声明函数控制块结构体
typedef struct
{
	unsigned char *Task_SP;      //函数堆栈指针
} TASK_TCB;

//定义TCB
TASK_TCB task1_tcb;
TASK_TCB task2_tcb;

void task1(void)
{
	while(1)
	{
		a=1;
		b=0;
    TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
		platform_delay_xms(1000);		//延时
		Task_Sched_2();//切换到函数2
	}
}

void task2(void)
{
	while(1)
	{
		a=0;
		b=1;
    TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
		platform_delay_xms(100);//延时
		Task_Sched_1();//切换到函数1
	}
}


void main(void)
{
    //保存堆栈指针和函数入口
  TINY51_OS_GPIO1_0 = 0;
	task1_tcb.Task_SP = task1_stack;
	task1_stack[0]= (unsigned char)task1;
	task1_stack[1]= (unsigned char)task1>>8;
    //偏移堆栈
	task1_tcb.Task_SP += 14;
    //保存堆栈指针和函数入口
	task2_tcb.Task_SP = task2_stack;
	task2_stack[0]= (unsigned char)task2;
	task2_stack[1]= (unsigned char)task2>>8;
    //偏移堆栈
	task2_tcb.Task_SP += 14;
    //切换到函数1
	Task_Sched_1();
	while(1);
}

void Task_Sched_1(void)
{

  __asm__("PUSH ACC");       //保护当前寄存器，压栈
  __asm__("PUSH B");
  __asm__("PUSH PSW");
  __asm__("PUSH DPL");
  __asm__("PUSH DPH");
  __asm__("PUSH 0");        //0-7为工作寄存器
  __asm__("PUSH 1");
  __asm__("PUSH 2");
  __asm__("PUSH 3");
  __asm__("PUSH 4");
  __asm__("PUSH 5");
  __asm__("PUSH 6");
  __asm__("PUSH 7");
  SP = (task1_tcb.Task_SP);
  __asm__("POP 7");         //恢复目标函数寄存器
  __asm__("POP 6");
  __asm__("POP 5");
  __asm__("POP 4");
  __asm__("POP 3");
  __asm__("POP 2");
  __asm__("POP 1");
  __asm__("POP 0");
  __asm__("POP DPH");
  __asm__("POP DPL");
  __asm__("POP PSW");
  __asm__("POP B");
  __asm__("POP ACC");
}

void Task_Sched_2(void)
{
  TINY51_OS_GPIO1_4 = 0;
  __asm__("PUSH ACC");       //保护当前寄存器，压栈
  __asm__("PUSH B");
  __asm__("PUSH PSW");
  __asm__("PUSH DPL");
  __asm__("PUSH DPH");
  __asm__("PUSH 0");        //0-7为工作寄存器
  __asm__("PUSH 1");
  __asm__("PUSH 2");
  __asm__("PUSH 3");
  __asm__("PUSH 4");
  __asm__("PUSH 5");
  __asm__("PUSH 6");
  __asm__("PUSH 7");
  SP = (task2_tcb.Task_SP);
  __asm__("POP 7");         //恢复目标函数寄存器
  __asm__("POP 6");
  __asm__("POP 5");
  __asm__("POP 4");
  __asm__("POP 3");
  __asm__("POP 2");
  __asm__("POP 1");
  __asm__("POP 0");
  __asm__("POP DPH");
  __asm__("POP DPL");
  __asm__("POP PSW");
  __asm__("POP B");
  __asm__("POP ACC");
}


#if 0
void task0(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_0 = !TINY51_OS_GPIO1_0;
    //platform_delay_xms(100);
  }
}

void task1(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_1 = !TINY51_OS_GPIO1_1;
    //platform_delay_xms(200);
  }
}

void task2(void)
{
  while (1)
  {
    TINY51_OS_GPIO1_2 = !TINY51_OS_GPIO1_2;
    //platform_delay_xms(300);
  }
}

void main(void)
{
  //lcd1602_init();
  // lcd1602_position_x_y(0);
  // lcd1602_write_string(5, 0, "Happy");
  // lcd1602_write_string(5, 1, "10.1");
  platform_timer_init_10ms();
  tiny51_init_task_scheduling();
  tiny51_register_task_scheduling(1, task0);
  tiny51_register_task_scheduling(2, task1);
  tiny51_register_task_scheduling(3, task2);
  tiny51_task_start(0);
  while (1)
  {
    TINY51_OS_GPIO1_3 = !TINY51_OS_GPIO1_3;
  }

}

uint8_t read_register(uint8_t address) {
  uint8_t value;
  uint8_t *ptr = (uint8_t *)address;
  value = *ptr;
  return value;
}

void write_register(uint8_t address, uint8_t value) {
  uint8_t *ptr = (uint8_t *)address;
  *ptr = value;
}

void platform_timer_init_10ms_interrupt(void) __interrupt(1)
{
  PLATFORM_OPEN_IRQ(0);

  TH0 = 0xD8;
  TL0 = 0xF0;

  // tiny51_task[tiny51_get_current_task()].ACC = read_register(SP);
  // tiny51_task[tiny51_get_current_task()].B = read_register(SP+1);
  // tiny51_task[tiny51_get_current_task()].PSW = read_register(SP+2);
  // tiny51_task[tiny51_get_current_task()].DPL = read_register(SP+3);
  // tiny51_task[tiny51_get_current_task()].DPH = read_register(SP+4);
  // tiny51_task[tiny51_get_current_task()].ar0 = read_register(SP+5);
  // tiny51_task[tiny51_get_current_task()].ar1 = read_register(SP+6);
  // tiny51_task[tiny51_get_current_task()].ar2 = read_register(SP+7);
  // tiny51_task[tiny51_get_current_task()].ar3 = read_register(SP+8);
  // tiny51_task[tiny51_get_current_task()].ar4 = read_register(SP+9);
  // tiny51_task[tiny51_get_current_task()].ar5 = read_register(SP+10);
  // tiny51_task[tiny51_get_current_task()].ar6 = read_register(SP+11);
  // tiny51_task[tiny51_get_current_task()].ar7 = read_register(SP+12);

  tiny51_task[tiny51_get_current_task()].stack_top = SP;
  tiny51_task[tiny51_get_current_task()].status = TINY51_OS_STATUS_READY;
  tiny51_task[tiny51_get_next_task()].status = TINY51_OS_STATUS_RUNING;
  SP = tiny51_task[tiny51_get_current_task()].stack_top;

  write_register(SP, tiny51_task[tiny51_get_current_task()].ACC);
  write_register(SP+1, tiny51_task[tiny51_get_current_task()].B);
  write_register(SP+2, tiny51_task[tiny51_get_current_task()].PSW);
  write_register(SP+3, tiny51_task[tiny51_get_current_task()].DPL);
  write_register(SP+4, tiny51_task[tiny51_get_current_task()].DPH);
  write_register(SP+5, tiny51_task[tiny51_get_current_task()].ar0);
  write_register(SP+6, tiny51_task[tiny51_get_current_task()].ar1);
  write_register(SP+7, tiny51_task[tiny51_get_current_task()].ar2);
  write_register(SP+8, tiny51_task[tiny51_get_current_task()].ar3);
  write_register(SP+9, tiny51_task[tiny51_get_current_task()].ar4);
  write_register(SP+10, tiny51_task[tiny51_get_current_task()].ar5);
  write_register(SP+11, tiny51_task[tiny51_get_current_task()].ar6);
  write_register(SP+12, tiny51_task[tiny51_get_current_task()].ar7);

  PLATFORM_OPEN_IRQ(1);
  PLATFORM_NOP(1);
}
#endif
