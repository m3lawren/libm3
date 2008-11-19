#ifndef _PQUEUE_H_
#define _PQUEUE_H_

/*
 * Priority queue implementation. Allows for O(1) removal and O(logn)
 * insertion. Duplicates are allowed.
 */

struct pqueue;

/*
 * Comparator function for the priority queue. Returns non-zero iff a has a 
 * higher "priority" than b.
 */
typedef int (*pqueue_compare)(void* a, void* b);

/*
 * _create   - Creates a new priority queue with the given comparator function.
 * _insert   - Inserts a given element into the queue. Duplicates are allowed.
 * _pop      - Removes the highest priority element from the queue.
 * _peek     - Returns the highest priority element in the queue, but does not
 *             modify the queue in any way.
 * _is_empty - Returns non-zero if the queue is empty.
 */
struct pqueue* pqueue_create(pqueue_compare);
void           pqueue_destroy(struct pqueue*);
void           pqueue_insert(struct pqueue*, void*);
void*          pqueue_pop(struct pqueue*);
void*          pqueue_peek(const struct pqueue*);
int            pqueue_is_empty(const struct pqueue*);

#endif
