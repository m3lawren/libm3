#include <stdio.h>
#include <stdlib.h>

#include <test.h>

void array_tests(int*, int*);
void pqueue_tests(int*, int*);
void queue_tests(int*, int*);

int main(int argc, char** argv) {
	int npass, nfail;
	npass = nfail = 0;

	if (argc != 1) {
		debug_func = argv[1];
	}
	
	array_tests(&npass, &nfail);
	pqueue_tests(&npass, &nfail);
	queue_tests(&npass, &nfail);

	printf("%d/%d tests passed\n", npass, npass + nfail);
	return 0;
}
