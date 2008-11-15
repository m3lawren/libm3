#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <test.h>

char* debug_func = "";

void debug_func_hit() {
}

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
	if (strcmp(tname, debug_func) == 0) {
		debug_func_hit();
	}
	if ((pid = fork())) {
		waitpid(pid, &status, 0);
		return status;
	} else {
		f(tname, outfile);
		fprintf(outfile, "\t[%s:PASS]\n", tname);
		fclose(outfile);
		exit(0);
	}
#endif
}