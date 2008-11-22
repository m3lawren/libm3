#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* debug_func;
void debug_func_hit();

typedef int (*test_func)(char*, FILE*);

int run_test(test_func f, char* tname, FILE*);

/*
 * Suite-related functions.
 */
#define T_SUITE(name) void name(int* npass, int* nfail) { _T_INIT_SUITE(name)
#define T_END_SUITE fclose(output); if (*nfail != init_nfail) { char buf[256]; int amt_read; fprintf(stdout, "[%s:FAIL]\n", sname); while ((amt_read = read(out_fds[0], buf, 256))) { fwrite(buf, 1, amt_read, stdout); } } else { fprintf(stdout, "[%s:PASS]\n", sname); } close(out_fds[0]); }
#define T_ADD_TEST(name) if (run_test(_t_##name, #name, output)) { (*nfail)++; } else { (*npass)++; }
#define _T_INIT_SUITE(name) char* sname = #name; int init_nfail = *nfail; int out_fds[2]; FILE* output; pipe(out_fds); output = fdopen(out_fds[1], "w");

/*
 * Test-related functions.
 */
#define T_TEST(name) static int _t_##name(char* _tname, FILE* _output) {
#define T_END_TEST return 0; }
#define T_ASSERT(x) if (!(x)) { fprintf(_output, "\t[%s:FAIL] %s:%d %s\n", _tname, __FILE__, __LINE__, #x); _T_BAILOUT; }


#ifdef T_NO_FORK
#define _T_BAILOUT return 1
#else
#define _T_BAILOUT exit(1)
#endif

#endif
