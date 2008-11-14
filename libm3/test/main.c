#include <stdio.h>
#include <stdlib.h>

void pqueue_tests(int*, int*);

int main(void) {
	int npass, nfail;
	npass = nfail = 0;

	pqueue_tests(&npass, &nfail);
	return 0;
}
