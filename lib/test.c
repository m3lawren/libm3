#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <test.h>

int run_test(test_func f, char* tname, FILE* outfile) {
	int status;

	fprintf(outfile, "  Running test %s...", tname);
	fflush(outfile);
	if (!(status = f(tname, outfile))) {
		int n = strlen("  Running test ...") + strlen(tname); 
		fputc('\r', outfile);
		while (n--) {
			fputc(' ', outfile);
		}
		fputc('\r', outfile);
	}
	return status;
}
