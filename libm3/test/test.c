#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "test.h"

int run_test(test_func f, char* tname, FILE* outfile) {
#ifdef T_NO_FORK
	int status;

	if (!(status = f(tname, outfile))) {
		fprintf(outfile, "\t[%s:PASS]\n", tname);
	}
	return status;
#else
	pid_t pid;
	int status;
	if ((pid = fork())) {
		waitpid(pid, &status, 0);
		return status;
	} else {
		f(tname, outfile);
		fprintf(outfile, "\t[%s:PASS]\n", tname);
		exit(0);
	}
#endif
}
