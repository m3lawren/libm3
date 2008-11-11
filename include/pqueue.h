#ifndef _PQUEUE_H_
#define _PQUEUE_H_

struct pqueue;

typedef int (*pqueue_compare)(void*, void*);

struct pqueue* pqueue_create(pqueue_compare);
void pqueue_destroy(struct pqueue*);

#endif
