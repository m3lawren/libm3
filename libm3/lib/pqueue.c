#include <pqueue.h>

#include <errno.h>
#include <stdlib.h>

struct pqueue {
	pqueue_compare f;
	unsigned long n;
	unsigned long s;
	void** a;
};

#define PAR(x) (((x) - 1) / 2)
#define LC(x) (((x) * 2) + 1)
#define RC(x) (((x) * 2) + 2)
#define SWAP(x, y) { void* t = q->a[x]; q->a[x] = q->a[y]; q->a[y] = t; }

/*****************************************************************************/
static void pqueue_bubble_up(struct pqueue* q) {
	unsigned long i = q->n - 1;
	while (i) {
		if (q->f(q->a[i], q->a[PAR(i)])) {
			SWAP(i, PAR(i));
			i = PAR(i);
		} else {
			break;
		}
	}
}

/*****************************************************************************/
static void pqueue_trickle_down(struct pqueue* q) {
	unsigned long i = 0;

	while (LC(i) < q->n) {
		unsigned long wc = LC(i);
		if (RC(i) < q->n && q->f(q->a[RC(i)], q->a[RC(i)])) {
			wc = RC(i);
		}
		if (q->f(q->a[wc], q->a[i])) {
			SWAP(wc, i);
			i = wc;
		}
	}
}

/*****************************************************************************/
struct pqueue* pqueue_create(pqueue_compare f) {
	struct pqueue* q = malloc(sizeof(struct pqueue*));
	if (!q) {
		return NULL;
	}

	q->f = f;
	q->n = 0;
	q->s = 4;
	q->a = malloc(sizeof(void*) * q->s);
	if (!q->a) {
		free(q);
		return NULL;
	}

	return q;
}

/*****************************************************************************/
void pqueue_destroy(struct pqueue* q) {
	if (!q) {
		return;
	}

	if (q->a) {
		free(q->a);
	}
	free(q);
}

/*****************************************************************************/
int pqueue_insert(struct pqueue* q, void* v) {
	if (!q) {
		return EINVAL;
	}

	if (q->n == q->s) {
		void** a = realloc(q->a, q->s * 2);
		if (!a) {
			return errno;
		}

		q->a = a;
		q->s *= 2;
	}

	q->a[q->n] = v;
	q->n++;

	pqueue_bubble_up(q);

	return 0;
}

/*****************************************************************************/
int pqueue_pop(struct pqueue* q, void** r) {
	if (!r) {
		return EINVAL;
	}

	*r = 0;

	if (!q || !q->n) {
		return EINVAL;
	}
	
	*r = q->a[0];

	q->n--;
	q->a[0] = q->a[q->n];
	pqueue_trickle_down(q);
	
	return 0;
}
