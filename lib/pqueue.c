#include <pqueue.h>

#include <stdlib.h>

struct pqueue {
	pqueue_compare f;
	unsigned long n;
	unsigned long s;
	void** a;
};

struct pqueue* pqueue_create(pqueue_compare f) {
	struct pqueue* q = malloc(sizeof(struct pqueue*));
	if (!q) {
		return NULL;
	}

	q->f = f;
	q->n = q->s = 0;
	q->a = NULL;

	return q;
}

void pqueue_destroy(struct pqueue* q) {
	if (!q) {
		return;
	}

	if (q->a) {
		free(q->a);
	}
	free(q);
}
