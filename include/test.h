#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>

extern char* debug_func;
void debug_func_hit();

typedef int (*test_func)(char*, FILE*);

int run_test(test_func f, char* tname, FILE*);

/*
 * Suite-related functions.
 */
#define T_SUITE(name) void name(int* npass, int* nfail) { _T_INIT_SUITE(name)
#define T_END_SUITE } 
#define T_ADD_TEST(name) if (run_test(_t_##name, #name, output)) { (*nfail)++; } else { (*npass)++; }
#define _T_INIT_SUITE(name) char* sname = #name; FILE* output = stdout; fprintf(output, "Running suite %s...\n", sname);

/*
 * Test-related functions.
 */
#define T_TEST(name) static int _t_##name(char* _tname, FILE* _output) {
#define T_END_TEST (void)_tname; (void)_output; return 0; }
#define T_ASSERT(x) if (!(x)) { fprintf(_output, " FAIL\n    Location: %s:%d\n    Assertion: %s\n", __FILE__, __LINE__, #x); return 1; }

#endif
