#include <test.h>

#include <array.h>

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
		T_ASSERT(num - i == (unsigned int)array_get(a, i));
	}
	
	T_ASSERT(num == array_size(a));
	T_ASSERT(0 == array_resize(a, num >> 1));
	T_ASSERT(num >> 1 == array_size(a));

	for (i = 0; i < num >> 1; i++) {
		T_ASSERT(num - i == (unsigned int)array_get(a, i));
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
			T_ASSERT(0 == array_insert(a, array_get(a, i - 1), i));
		}
	}

	T_ASSERT(num * 2 == array_size(a));

	for (i = 0; i < num * 2; i++) {
		T_ASSERT(i >> 1 == (unsigned int)array_get(a, i));
	}

	for (i = 0; i < num; i++) {
		T_ASSERT(0 == array_append(a, (void*)(i + num)));
	}
	
	T_ASSERT(num * 3 == array_size(a));

	for (i = 0; i < num * 3; i++) {
		if (i < num * 2) {
			T_ASSERT(i >> 1 == (unsigned int)array_get(a, i));
		} else {
			T_ASSERT(i - num == (unsigned int)array_get(a, i));
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

} T_END_SUITE
