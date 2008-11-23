#include <stdio.h>
#include <stdlib.h>

#include <test.h>

void pqueue_tests(int*, int*);
void queue_tests(int*, int*);

int main() {
	int npass, nfail;
	npass = nfail = 0;

	pqueue_tests(&npass, &nfail);
	queue_tests(&npass, &nfail);

	printf("%d/%d tests passed\n", npass, npass + nfail);
	return 0;
}
