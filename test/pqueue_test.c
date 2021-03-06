#include <pqueue.h>

#include <test.h>

static int comp(void* a, void* b) {
	return (int)a < (int)b;
}

T_TEST(t_pqueue_basic) {
	struct pqueue* q = pqueue_create(comp);
	
	T_ASSERT(q != NULL);

	pqueue_destroy(q);

} T_END_TEST

T_TEST(t_pqueue_inorder_insert) {
	struct pqueue* q = pqueue_create(comp);
	int i;
	int num = 10;

	T_ASSERT(q);

	for (i = 0; i < num; i++) {
		T_ASSERT(0 == pqueue_insert(q, (void*)i));
	}

	T_ASSERT(!pqueue_is_empty(q));

	i = 0;
	while (!pqueue_is_empty(q)) {
		T_ASSERT(i == (int)pqueue_peek(q));
		T_ASSERT(i == (int)pqueue_pop(q));
		i++;
	}

	T_ASSERT(i == num);

	pqueue_destroy(q);

} T_END_TEST

T_TEST(t_pqueue_alt_insert) {
	struct pqueue* q = pqueue_create(comp);
	int i;
	int num = 10;

	T_ASSERT(q);

	for (i = 0; i < num; i++) {
		T_ASSERT(0 == pqueue_insert(q, (void*)((i % 2) ? i : num - i - (num % 2 ? 1 : 2))));
	}
	
	T_ASSERT(!pqueue_is_empty(q));

	i = 0;
	while (!pqueue_is_empty(q)) {
		T_ASSERT(i == (int)pqueue_peek(q));
		T_ASSERT(i == (int)pqueue_pop(q));
		i++;
	}

	T_ASSERT(i == num);

	pqueue_destroy(q);
} T_END_TEST

T_TEST(t_pqueue_duplicate) {
	struct pqueue* q = pqueue_create(comp);
	void* v = (void*)0xdeadbeef;

	T_ASSERT(q);

	T_ASSERT(0 == pqueue_insert(q, v));
	T_ASSERT(0 == pqueue_insert(q, v));

	T_ASSERT(!pqueue_is_empty(q));
	T_ASSERT(v == pqueue_peek(q));
	T_ASSERT(v == pqueue_pop(q));
	
	T_ASSERT(!pqueue_is_empty(q));
	T_ASSERT(v == pqueue_peek(q));
	T_ASSERT(v == pqueue_pop(q));

	T_ASSERT(pqueue_is_empty(q));

	pqueue_destroy(q);

} T_END_TEST

T_TEST(t_pqueue_destroy_null) {
	pqueue_destroy(NULL);
} T_END_TEST

T_TEST(t_pqueue_destroy_empty) {
	struct pqueue* q = pqueue_create(comp);
	pqueue_destroy(q);
} T_END_TEST

T_SUITE(pqueue_tests) {

	T_ADD_TEST(t_pqueue_basic);
	T_ADD_TEST(t_pqueue_inorder_insert);
	T_ADD_TEST(t_pqueue_alt_insert);
	T_ADD_TEST(t_pqueue_duplicate);
	T_ADD_TEST(t_pqueue_destroy_null);
	T_ADD_TEST(t_pqueue_destroy_empty);

} T_END_SUITE
