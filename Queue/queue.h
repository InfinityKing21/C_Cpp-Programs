#ifndef QUEUE
#define QUEUE

// Change queue implementation here
typedef struct static_circular_queue queue_impl;
#include "static_circular_queue_impl.c"
//

typedef queue_impl queue;
typedef int queue_data_type;
typedef int return_status;

return_status init_queue(queue_impl *Q, int size);
return_status is_full(queue_impl Q);
return_status is_empty(queue_impl Q);
return_status enqueue(queue_impl *Q, queue_data_type val);

// Check if empty before getting front
queue_data_type front(queue_impl Q);

return_status dequeue(queue_impl *Q);
void destruct(queue_impl *Q);
void print_queue(queue_impl Q);

#endif
