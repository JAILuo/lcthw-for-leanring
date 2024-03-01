#ifndef _QUEUE_H
#define _QUEUE_H

#include <lcthw/list.h>


typedef List Queue;


#define Queue_create() List_create()

#define Queue_destroy(queue) List_destroy(queue)

#define Queue_send(queue, value) List_unshift(queue, value)

#define Queue_recv(queue) List_pop(queue)


#define Queue_count(A) (A->count)
#define Queue_peek(A) (A->last != NULL ? A->last->value : NULL)



#define QUEUE_FOREACH(queue, cur) \
    LIST_FOREACH( queue, first, next, cur )








#endif

