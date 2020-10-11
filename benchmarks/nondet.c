/**
 * This benchmark fails whenever the dividend is 0.
 * This can be the case if either x (the input) or y (an allocated, nondeterministic variable) is 0
 * Therefore the assertion miss is NOT ONLY dependent on the input x, but also depends on nondeterminism.
 * Closer examination shows that the assertion MUST fail for x<=0, but MAY fail for any x
 */

#include<malloc.h>

int testfun(int x) {
	if (x<0) {
		x=0;
	}
	int *y = malloc(sizeof(int));
	int div = (*y) * x;
	__counterSharp_assert(div!=0);
	return 100/div;
}
