#include <queue.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct queue {
	void** a;
	unsigned int sz;  /* Size of a */
	unsigned int num; /* Number of elements */
	unsigned int idx; /* Start index in a */
};

/*****************************************************************************/
struct queue* queue_create() {
	struct queue* q = malloc(sizeof(struct queue));

	if (!q) {
		return NULL;
	}

	q->a = NULL;
	q->sz = q->num = q->idx = 0;

	return q;
}

/*****************************************************************************/
int queue_destroy(struct queue* q) {
	if (!q) {
		return EINVAL;
	}

	if (q->a) {
		free(q->a);
	}
	free(q);

	return 0;
}

/*****************************************************************************/
int queue_push(struct queue* q, void* v) {
	unsigned int nidx;

	if (q == NULL) {
		return EINVAL;
	}

	if (q->num == q->sz) {
		unsigned int nsz = q->sz << 1;
		void** na;

		if (nsz == 0) {
			nsz = 4;
		}

		na = realloc(q->a, nsz * sizeof(void*));	

		if (!na) {
			return ENOMEM;
		}

		/* If we were wrapping before, we need to unwrap. Since we're doubling,
		 * we know that we have enough space to do this. */
		if (q->sz && q->idx) {
			memcpy(&na[q->sz], na, q->idx * sizeof(void*));
		}
		
		q->a = na;
		q->sz = nsz;
	}

	nidx = q->num + q->idx;
	if (nidx >= q->sz) {
		nidx -= q->sz;
	}
	q->a[nidx] = v;
	q->num++;

	return 0;
}

/*****************************************************************************/
int queue_pop(struct queue* q, void** ret) {
	if (ret == NULL) {
		return EINVAL;
	}

	*ret = NULL;

	if (q == NULL) {
		return EINVAL;
	}
	if (queue_is_empty(q)) {
		return EINVAL;
	}

	*ret = q->a[q->idx];

	q->idx++;
	q->idx %= q->sz;
	q->num--;

	return 0;
}

/*****************************************************************************/
int queue_peek(struct queue* q, void** ret) {
	if (ret == NULL) {
		return EINVAL;
	}
	
	*ret = NULL;

	if (q == NULL) {
		return EINVAL;
	}
	if (queue_is_empty(q)) {
		return EINVAL;
	}

	*ret = q->a[q->idx];

	return 0;
}

/*****************************************************************************/
int queue_is_empty(struct queue* q) {
	if (q == NULL) {
		return 1;
	}
	if (q->num == 0) {
		return 1;
	}
	return 0;
}
