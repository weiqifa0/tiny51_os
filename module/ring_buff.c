/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2024
*/
#include "ring_buff.h"

struct ring_buff * ring_buff_init(void)
{
  struct ring_buff * p = NULL;
  p = (struct ring_buff *)malloc(sizeof(struct ring_buff));
  if(p == NULL)
  {
    return NULL;
  }
  p->W = 0;
  p->R = 0;
  return p;
}

int get_ring_buff_fullstate(struct ring_buff * p_ring_buff)
{
  if((p_ring_buff->W - p_ring_buff->R) == LEN)
  {
    return (1);
  }
  return (0);
}

int get_ring_buff_emptystate(struct ring_buff * p_ring_buff)
{
  if(p_ring_buff->W == p_ring_buff->R)
  {
    return (1);
  }
  return (0);
}

int ring_buff_insert(struct ring_buff * p_ring_buff,int tmp)
{
  if(p_ring_buff == NULL)
  {
    return (-1);
  }

  if(get_ring_buff_fullstate(p_ring_buff) == 1)
  {
    return (-2);
  }

  //p_ring_buff->array[p_ring_buff->W%LEN] = data;
  p_ring_buff->array[p_ring_buff->W&(LEN -1)] = tmp;
  p_ring_buff->W ++;
  return (0);
}

int ring_buff_get(struct ring_buff * p_ring_buff)
{
  int tmp = 0;

  if(p_ring_buff == NULL)
  {
    return (-1);
  }

  if(get_ring_buff_emptystate(p_ring_buff) == 1)
  {
    return (-2);
  }

  //data = p_ring_buff->array[p_ring_buff->R%LEN];
  tmp = p_ring_buff->array[p_ring_buff->R&(LEN -1)];
  p_ring_buff->R++;
  return tmp;
}

int ring_buff_destory(struct ring_buff * p_ring_buff)
{
  if(p_ring_buff == NULL)
  {
    return (-1);
  }

  free(p_ring_buff);

  return (0);
}