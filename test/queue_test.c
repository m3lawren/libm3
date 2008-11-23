#include <queue.h>

#include <test.h>

T_TEST(t_queue_basic) {
	struct queue* q = queue_create();

	T_ASSERT(q != NULL);
	T_ASSERT(queue_is_empty(q));
	queue_destroy(q);

} T_END_TEST

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
		T_ASSERT(i == (int)queue_peek(q));
		T_ASSERT(i == (int)queue_pop(q));
	}

	T_ASSERT(queue_is_empty(q));

	queue_destroy(q);

} T_END_TEST

T_TEST(t_queue_destroy_null) {
	queue_destroy(NULL);
} T_END_TEST

T_TEST(t_queue_test_wrapping) {
	int num = 4;
	int i;
	struct queue* q = queue_create();

	for (i = 0; i < num; i++) {
		T_ASSERT(queue_push(q, (void*)i) == 0);
	}

	for (i = 0; i < num >> 1; i++) {
		T_ASSERT(i == (int)queue_pop(q));
		T_ASSERT(0 == queue_push(q, (void*)i));
	}

	T_ASSERT(0 == queue_push(q, (void*)(num >> 1)));

	for (i = 0; i < num + 1; i++) {
		T_ASSERT((i + 1 + (num >> 2)) % num == (int)queue_pop(q));
	}
	T_ASSERT(queue_is_empty(q));

	queue_destroy(q);
} T_END_TEST

T_SUITE(queue_tests) {
	
	T_ADD_TEST(t_queue_basic);
	T_ADD_TEST(t_queue_insert);
	T_ADD_TEST(t_queue_destroy_null);
	T_ADD_TEST(t_queue_test_wrapping);

} T_END_SUITE
