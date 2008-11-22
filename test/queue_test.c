#include <queue.h>

#include <test.h>

T_TEST(t_queue_basic) {
	struct queue* q = queue_create();

	T_ASSERT(q != NULL);
	T_ASSERT(queue_is_empty(q));
	queue_destroy(q);

	T_END_TEST;
}

T_TEST(t_queue_insert) {
	int num = 16;
	struct queue* q = queue_create();
	int i;

	for (i = 0; i < num; i++) {
		T_ASSERT(queue_push(q, (void*)i) == 0);
		T_ASSERT(!queue_is_empty(q));
	}

	for (i = 0; i < num; i++) {
		T_ASSERT(!queue_is_empty(q));
		T_ASSERT(i == (int)queue_pop(q));
	}

	T_ASSERT(queue_is_empty(q));

	queue_destroy(q);

	T_END_TEST;
}

T_SUITE(queue_tests) {
	T_INIT_SUITE(queue_tests);
	
	T_ADD_TEST(t_queue_basic);
	T_ADD_TEST(t_queue_insert);

	T_END_SUITE;
}
