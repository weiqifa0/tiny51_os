/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/

#include "chip_platform/platform_head.h"
#include "machine_hal/machine_config.h"
#include "task_scheduling_core/task_scheduling_core.h"

#define uint unsigned int
#define uchar unsigned char
#define taskNum 3
#define taskStackLen 13

int a;
#define led0 TINY51_OS_GPIO1_1
#define led1 TINY51_OS_GPIO1_2
#define led2 TINY51_OS_GPIO1_3
#define led3 TINY51_OS_GPIO1_4

uchar flag=0,num=0;
uchar *pstk[taskNum];
uchar temp,i;
uint delayList[3]={0,0,0};
uchar interruptedList[3]={0,0,0};

void osDelay(uint delayTime, uchar n){
  delayList[n]= delayTime*0.903; //这个相当于是乘以一个数，让它稍微小一点。
  interruptedList[n]=1;
    while(1){
      if(interruptedList[n]==0)	{
        break;
    }
  }
}

void delay(uint z) {
 static unsigned int x, y;
 for(x=z; x>0; x--)
  for(y=110; y>0; y--);  //原来为110
}

int detect() {	//模拟的任务执行函数。比如……调用超声波。
	delay(2);
	led3 = !led3;
	delay(2);
	return 0;
}
void InitTimer0(void) {
	TMOD = 0x01;
  TH0 = 0x0FC;
  TL0 = 0x18;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
}


void taskA() {
 while(1) {
  temp=0x01;
  led0 = !led0;
  osDelay(10,0);
 }
}
void taskB() {
static int b;
 while(1) {
  led1 = !led1;
  b=detect();
  osDelay(1000,1);
 }
}

void taskC() {
 while(1) {
  delay(20);
 }
}

void main(void) {
 InitTimer0();
 while(1){

 };
}
void * const func[]={taskA,taskB,taskC};

void exint0() __interrupt (1)
{

  uchar __idata *p;
  uchar q;

  led2 = !led2;

  if(num==1) pstk[0]=(uchar *)SP;//num=1表示第二次进入中断（主函数中没有任务运行），在进入任务后产生的中断，这时保存该任务的进入中断前的堆栈指针
  if((num==2)&&(num==taskNum-1)) pstk[1]=(uchar *)SP;	 //第三次进入中断的时候需要


  //执行这一步！但是为什么呢？
  if(num<taskNum)		   //这种情况有几个任务就在初次启动时启动几次。
  {
    p = (uchar __idata *)SP+1;	//将SP强制类型转换为UCHAR类型的指针，并且在SP的地址的基础上加1。
    *p++=((uint)(func[num]))%256;
    *p=((uint)(func[num]))/256;   //将右边赋给p指针所指向的地址。这里指的是，取出func[num]这个函数的首地址，除以256之后再赋给p指向的地址。
    SP=(uchar)p;          	    //	强制类型转换，让SP指向p的地址。
    SP+=10;	                   // 我不懂这句是啥意思……
    num++;	                	//当前的任务号:自增。
                                //这一部分应该能自动增加。
  }
  else
  {
    static unsigned char lastFlag=2;

    flag=2;
    q=flag;
    if(delayList[0]>0) {
      delayList[0]-=1;
    }else{
      q=flag;
      flag=0;
    }

    if(delayList[1]>0){
      delayList[1]-=1;
    }else{
      q=flag;
      flag=1;
    }
    interruptedList[0]=0;
    interruptedList[1]=0;
    interruptedList[2]=0;


    pstk[lastFlag]=	 (uchar *)SP;
    lastFlag = flag;
    SP = (uchar)pstk[flag];
  }
  TH0 = 0x0FC;
  TL0 = 0x18;
}
//此程序是通过定时器中断来切换的,但是切换时对堆栈的使用上存在问题。
//该程序的目的不是展示完美的任务级切换,主要是如何切换的问题。



