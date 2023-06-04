#ifndef CIRCULAR_QUEUE_IMPL
#define CIRCULAR_QUEUE_IMPL

#include<stdio.h>
#include<stdlib.h>

typedef int queue_data_type;
typedef int return_status;

typedef struct static_circular_queue
{
    queue_data_type *arr;
    int size;
    int head;
    int tail;
} SCQ;

return_status init_queue(SCQ *Q, int size)
{
    Q->arr = malloc(size * sizeof(*(Q->arr)));
    Q->size = 0;

    // Failed to init queue
    if(!Q->arr)
        return 0;

    Q->size = size;
    Q->head = Q->tail = -1;

    return 1;
}

return_status is_full(SCQ Q)
{
    if((Q.tail + 1) % Q.size == Q.head)
        return 1;

    return 0;
}

return_status is_empty(SCQ Q)
{
    if(Q.head == -1)
        return 1;

    return 0;
}

return_status enqueue(SCQ *Q, int val)
{
    if(is_full(*Q))
        return 0;

    if(is_empty(*Q))
    {
        Q->head = Q->tail = 0;
        Q->arr[Q->tail] = val;
        return 1;
    }

    ++Q->tail;
    Q->tail %= Q->size;
    Q->arr[Q->tail] = val;

    return 1;
}

// Check if empty before getting front
queue_data_type front(SCQ Q)
{
    return Q.arr[Q.head];
}

return_status dequeue(SCQ *Q)
{
    if(is_empty(*Q))
        return 0;

    if(Q->head == Q->tail)
    {
        Q->head = Q->tail = -1;
        return 1;
    }

    ++Q->head;
    Q->head %= Q->size;

    return 1;
}

void destruct(SCQ *Q)
{
    Q->size = 0;
    Q->head = Q->tail = -1;

    if(Q->arr)
        free(Q->arr);
}

void print_queue(SCQ Q)
{
    if(Q.head <= Q.tail)
        for(int i = Q.head; i <= Q.tail; ++i)
            printf("%d ", Q.arr[i]);
    else
    {
        for(int i = Q.head; i < Q.size; ++i)
            printf("%d ", Q.arr[i]);

        for(int i = 0; i <= Q.tail; ++i)
            printf("%d ", Q.arr[i]);
    }
}

#endif
