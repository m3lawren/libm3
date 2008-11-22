#ifndef _QUEUE_H_
#define _QUEUE_H_

/* 
 * FIFO queue implementation. Allows for O(1) pushing and popping.
 */

struct queue;

/*
 * _push     - Adds an element to the back of the queue. Returns 0 on success.
 * _pop      - Removes an element from the front of the queue.
 * _is_empty - Returns non-zero if the queue is empty.
 */
struct queue*  queue_create();
int            queue_push(struct queue*, void*);
void*          queue_pop(struct queue*);
int            queue_is_empty(struct queue*);

#endif
