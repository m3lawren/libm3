#include <pqueue.h>

#include "test.h"

int comp(void* a, void* b) {
	return (int)a - (int)b;
}

T_TEST(basic_fail) {
}

T_TEST(basic_pass) {
}

T_TEST(basic_assert_pass) {
	T_ASSERT(1 == 1, "This should not have failed.");
}

T_TEST(basic_assert_fail) {
	T_ASSERT(1 == 0, "Expected failure!");
}

T_SUITE(pqueue_tests) {
	T_INIT_SUITE(pqueue_tests); 

	T_ADD_TEST(basic_fail)
	T_ADD_TEST(basic_pass)
	T_ADD_TEST(basic_assert_fail);
	T_ADD_TEST(basic_assert_pass);

	T_END_SUITE;
}
