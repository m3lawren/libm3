#include <queue.h>

#include <errno.h>
#include <test.h>

T_TEST(t_queue_basic) {
	struct queue* q = queue_create();

	T_ASSERT(q != NULL);
	T_ASSERT(queue_is_empty(q));
	T_ASSERT(0 == queue_destroy(q));

} T_END_TEST

T_TEST(t_errors) {
	struct queue* q = queue_create();
	void* v = NULL;
	void*const V = (void*)0xdeadbeef;

	T_ASSERT(EINVAL == queue_push(NULL, NULL));

	/* queue_pop tests */
	T_ASSERT(EINVAL == queue_pop(q, NULL));

	v = V;
	T_ASSERT(EINVAL == queue_pop(NULL, &v));
	T_ASSERT(v == NULL);

	v = V;
	T_ASSERT(EINVAL == queue_pop(q, &v));
	T_ASSERT(v == NULL);
	
	/* queue_peek tests */
	T_ASSERT(EINVAL == queue_peek(q, NULL));

	v = V;
	T_ASSERT(EINVAL == queue_peek(NULL, &v));
	T_ASSERT(v == NULL);

	v = V;
	T_ASSERT(EINVAL == queue_peek(q, &v));
	T_ASSERT(v == NULL);

	/* queue_is_empty tests */
	T_ASSERT(1 == queue_is_empty(NULL));

	T_ASSERT(0 == queue_destroy(q));
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
		int x;
		T_ASSERT(!queue_is_empty(q));
		T_ASSERT(0 == queue_peek(q, (void**)&x))
		T_ASSERT(i == x);
		T_ASSERT(0 == queue_pop(q, (void**)&x));
		T_ASSERT(i == x);
	}

	T_ASSERT(queue_is_empty(q));

	T_ASSERT(0 == queue_destroy(q));

} T_END_TEST

T_TEST(t_queue_destroy_null) {
	T_ASSERT(EINVAL  == queue_destroy(NULL));
} T_END_TEST

T_TEST(t_queue_test_wrapping) {
	int num = 4;
	int i;
	struct queue* q = queue_create();

	for (i = 0; i < num; i++) {
		T_ASSERT(queue_push(q, (void*)i) == 0);
	}

	for (i = 0; i < num >> 1; i++) {
		int x;
		T_ASSERT(0 == queue_pop(q, (void**)&x));
		T_ASSERT(i == x);
		T_ASSERT(0 == queue_push(q, (void*)i));
	}

	T_ASSERT(0 == queue_push(q, (void*)(num >> 1)));

	for (i = 0; i < num + 1; i++) {
		int x;
		T_ASSERT(0 == queue_pop(q, (void**)&x));
		T_ASSERT((i + 1 + (num >> 2)) % num == x);
	}
	T_ASSERT(queue_is_empty(q));

	T_ASSERT(0 == queue_destroy(q));
} T_END_TEST

T_SUITE(queue_tests) {
	
	T_ADD_TEST(t_queue_basic);
	T_ADD_TEST(t_queue_insert);
	T_ADD_TEST(t_queue_destroy_null);
	T_ADD_TEST(t_queue_test_wrapping);
	T_ADD_TEST(t_errors);

} T_END_SUITE
