#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <test.h>

int run_test(test_func f, char* tname, FILE* outfile) {
	int status;

	if (!(status = f(tname, outfile))) {
		fprintf(outfile, "\t[%s:PASS]\n", tname);
	}
	return status;
}
