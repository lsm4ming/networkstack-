#pragma once

#include <stdlib.h>

#define BUFFER_SIZE 64;

typedef struct ring_queue_t
{
    int read_index;
    int write_index;
    char *buffer;
    int cap;
    int length;
} ring_queue_t;

// 创建环形队列
ring_queue_t *create_ring_queue(int cap);

// 销毁环形队列
void destroy_ring_queue(ring_queue_t *queue);

void ring_queue_insert(ring_queue_t *queue, char data);

char ring_queue_pop(ring_queue_t *queue);