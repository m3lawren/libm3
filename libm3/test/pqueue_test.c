#include <pqueue.h>

#include "test.h"

static int comp(void* a, void* b) {
	return (int)a < (int)b;
}

T_TEST(t_pqueue_basic) {
	struct pqueue* q = pqueue_create(comp);
	
	T_ASSERT(q != NULL);

	pqueue_destroy(q);

	T_END_TEST;
}

T_TEST(t_pqueue_inorder_insert) {
	struct pqueue* q = pqueue_create(comp);
	int i;

	T_ASSERT(q);

	for (i = 0; i < 10; i++) {
		pqueue_insert(q, (void*)i);
	}

	T_ASSERT(!pqueue_is_empty(q));

	i = 0;
	while (!pqueue_is_empty(q)) {
		T_ASSERT(i == (int)pqueue_peek(q));
		T_ASSERT(i == (int)pqueue_pop(q));
		i++;
	}

	T_ASSERT(i == 10);

	pqueue_destroy(q);

	T_END_TEST;
}

T_SUITE(pqueue_tests) {
	T_INIT_SUITE(pqueue_tests);

	T_ADD_TEST(t_pqueue_basic);
	T_ADD_TEST(t_pqueue_inorder_insert);

	T_END_SUITE;
}
