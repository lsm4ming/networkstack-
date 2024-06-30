#include "ring_queue.h"

// 创建环形队列
ring_queue_t *create_ring_queue(int cap)
{
    if (cap <= 0)
    {
        cap = BUFFER_SIZE;
    }
    ring_queue_t *queue = (ring_queue_t *)malloc(sizeof(ring_queue_t));
    if (!queue)
    {
        return NULL;
    }
    queue->buffer = (char *)malloc(cap);
    queue->cap = cap;
     queue->length = 0;
}

// 销毁环形队列
void destroy_ring_queue(ring_queue_t *queue)
{
    if (!queue)
    {
        return;
    }
    if (queue->buffer)
    {
        free(queue->buffer);
    }
    free(queue);
}

void ring_queue_insert(ring_queue_t *queue, char data)
{
    if (queue->length >= queue->cap + 1)
    {
        return;
    }
    queue->buffer[queue->write_index] = data;
    queue->write_index = (queue->write_index + 1) % queue->cap;
    queue->length++;
}

char ring_queue_pop(ring_queue_t *queue)
{
    if (queue->length == 0)
    {
        return 0;
    }
    char data = queue->buffer[queue->read_index];
    queue->read_index = (queue->read_index + 1) % queue->cap;
    queue->length--;
    return data;
}