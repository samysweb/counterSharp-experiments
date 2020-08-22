#include<assert.h>
#include<malloc.h>

int testfun(int x) {
	if (x<0) {
		x=0;
	}
	int *y = malloc(sizeof(int));
	int div = (*y) * x;
	assert(div!=0);
	return 100/div;
}