#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* debug_func;
void debug_func_hit();

typedef void (*test_func)(char*);

int run_test(test_func f, char* tname, int out_fd, int err_fd);

/*
 * Suite-related functions.
 */
#define T_SUITE(name) void name(int* npass, int* nfail)
#define T_INIT_SUITE(name) char* sname = #name; int init_nfail = *nfail; int out_fds[2]; int err_fds[2]; pipe(out_fds); pipe(err_fds);
#define T_END_SUITE { close(out_fds[1]); close(err_fds[1]); if (*nfail != init_nfail) { char buf[256]; int amt_read; fprintf(stdout, "[%s:FAIL]\n", sname); while ((amt_read = read(out_fds[0], buf, 256))) { fwrite(buf, 1, amt_read, stdout); } } else { fprintf(stdout, "[%s:PASS]\n", sname); } close(out_fds[0]); close(err_fds[0]);}
#define T_ADD_TEST(name) if (run_test(_t_##name, #name, out_fds[1], err_fds[1])) { (*nfail)++; } else { (*npass)++; }

/*
 * Test-related functions.
 */
#define T_TEST(name) static void _t_##name(char* tname)
#define T_INIT_TEST(name) 
#define T_ASSERT(x) if (!(x)) { fprintf(stdout, "\t[%s:FAIL] %s:%d %s\n", tname, __FILE__, __LINE__, #x); exit(1); }

#endif
