#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "test.h"

char* debug_func = "";

void debug_func_hit() {
}

int run_test(test_func f, char* tname, int out_fd, int err_fd) {
	pid_t pid;
	int status;
	if (strcmp(tname, debug_func) == 0) {
		debug_func_hit();
	}
	if ((pid = fork())) {
		waitpid(pid, &status, 0);
		return status;
	} else {
		close(1);
		dup(out_fd);
		close(2);
		dup(err_fd);
		f(tname);
		fprintf(stdout, "\t[%s:PASS]\n", tname);
		exit(0);
	}
}
