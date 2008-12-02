#include <test.h>

#include <array.h>
#include <errno.h>

T_TEST(t_array_error) {
	struct array* a = array_create();
	void* x;

	T_ASSERT(a != NULL);

	/* array_reserve tests */
	T_ASSERT(EINVAL == array_reserve(NULL, 0));

	/* array_resize tests */
	T_ASSERT(EINVAL == array_resize(NULL, 0));

	/* array_size tests */
	T_ASSERT(0 == array_size(NULL));

	/* array_set tests */
	T_ASSERT(EINVAL == array_set(NULL, 0, NULL));
	T_ASSERT(EINVAL == array_set(a, 0, NULL));

	/* array_get tests */
	T_ASSERT(EINVAL == array_get(a, 0, NULL));
	T_ASSERT(EINVAL == array_get(NULL, 0, &x));
	T_ASSERT(EINVAL == array_get(a, 0, &x));

	/* array_append tests */
	T_ASSERT(EINVAL == array_append(NULL, x));
	
	/* array_insert tests */
	T_ASSERT(EINVAL == array_insert(NULL, x, 0));
	T_ASSERT(EINVAL == array_insert(a, x, 1));

	T_ASSERT(0 == array_destroy(a));

} T_END_TEST

T_TEST(t_array_destroy_null) {
	array_destroy(NULL);
} T_END_TEST

T_TEST(t_array_destroy_empty) {
	struct array* a = array_create();
	array_destroy(a);
} T_END_TEST

T_TEST(t_array_reserve) {
	struct array* a = array_create();

	T_ASSERT(0 == array_reserve(a, 0));
	T_ASSERT(0 == array_reserve(a, 15));
	T_ASSERT(0 == array_reserve(a, 1));

	T_ASSERT(0 == array_size(a));

	array_destroy(a);
} T_END_TEST

T_TEST(t_array_resize) {
	struct array* a = array_create();

	T_ASSERT(0 == array_resize(a, 0));
	T_ASSERT(0 == array_size(a));
	T_ASSERT(0 == array_resize(a, 15));
	T_ASSERT(15 == array_size(a));
	T_ASSERT(0 == array_resize(a, 6));
	T_ASSERT(6 == array_size(a));
	T_ASSERT(0 == array_resize(a, 0));
	T_ASSERT(0 == array_size(a));

	array_destroy(a);
} T_END_TEST

T_TEST(t_array_setget) {
	struct array* a = array_create(a);
	unsigned int i, num = 17;

	T_ASSERT(0 == array_resize(a, num));
	T_ASSERT(num == array_size(a));

	for (i = 0; i < num; i++) {
		array_set(a, i, (void*)(num - i));
	}

	T_ASSERT(num == array_size(a));

	for (i = 0; i < num; i++) {
		unsigned int x;
		T_ASSERT(0 == array_get(a, i, (void**)&x));
		T_ASSERT(num - i == x);
	}
	
	T_ASSERT(num == array_size(a));
	T_ASSERT(0 == array_resize(a, num >> 1));
	T_ASSERT(num >> 1 == array_size(a));

	for (i = 0; i < num >> 1; i++) {
		unsigned int x;
		T_ASSERT(0 == array_get(a, i, (void**)&x));
		T_ASSERT(num - i == x); 
	}

	array_destroy(a);
} T_END_TEST

T_TEST(t_array_insertappend) {
	struct array* a = array_create(a);
	unsigned int i, num = 5;

	T_ASSERT(0 == array_resize(a, num));
		
	for (i = 0; i < num; i++) {
		array_set(a, i, (void*)i);
	}

	for (i = 0; i < num * 2; i++) {
		if (i % 2 == 1) {
			unsigned int x;
			T_ASSERT(0 == array_get(a, i - 1, (void**)&x));
			T_ASSERT(0 == array_insert(a, (void*)x, i));
		}
	}

	T_ASSERT(num * 2 == array_size(a));

	for (i = 0; i < num * 2; i++) {
		unsigned int x;
		T_ASSERT(0 == array_get(a, i, (void**)&x));
		T_ASSERT(i >> 1 == x);
	}

	for (i = 0; i < num; i++) {
		T_ASSERT(0 == array_append(a, (void*)(i + num)));
	}
	
	T_ASSERT(num * 3 == array_size(a));

	for (i = 0; i < num * 3; i++) {
		unsigned int x;
		T_ASSERT(0 == array_get(a, i, (void**)&x));
		if (i < num * 2) {
			T_ASSERT(i >> 1 == x);
		} else {
			T_ASSERT(i - num == x);
		}
	}

	array_destroy(a);

} T_END_TEST

T_SUITE(array_tests) {

	T_ADD_TEST(t_array_destroy_null);
	T_ADD_TEST(t_array_destroy_empty);
	T_ADD_TEST(t_array_reserve);
	T_ADD_TEST(t_array_resize);
	T_ADD_TEST(t_array_setget);
	T_ADD_TEST(t_array_insertappend);
	T_ADD_TEST(t_array_error);

} T_END_SUITE
