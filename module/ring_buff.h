/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2024
*/
#ifndef __RING_BUFF_H__
#define __RING_BUFF_H__

#include "stdio.h"
#include "stdlib.h"

#define LEN 16

typedef struct ring_buff{
	int array[LEN];
	int W;
	int R;
}* ring_buff;

struct ring_buff * ring_buff_init(void);
int ring_buff_insert(struct ring_buff * p_ring_buff, int tmp);
int ring_buff_get(struct ring_buff * p_ring_buff);
int ring_buff_destory(struct ring_buff * p_ring_buff);

#endif //__RING_BUFF_H__