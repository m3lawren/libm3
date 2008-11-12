#ifndef _PQUEUE_H_
#define _PQUEUE_H_

struct pqueue;

/*
 * Comparator function for the priority queue. Returns non-zero iff a has a 
 * higher "priority" than b.
 */
typedef int (*pqueue_compare)(void* a, void* b);

struct pqueue* pqueue_create(pqueue_compare);
void           pqueue_destroy(struct pqueue*);
void           pqueue_insert(struct pqueue*, void*);
void*          pqueue_pop(struct pqueue*);
void*          pqueue_peek(const struct pqueue*);
int            pqueue_is_empty(const struct pqueue*);

#endif
