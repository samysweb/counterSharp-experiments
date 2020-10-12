// Source: Thomas A. Henzinger, Thibaud Hottelier, Laura Kovacs: "Valigator:
// A verification Tool with Bound and Invariant Generation", LPAR 2008

#include "assert.h"

int main() {
    int a = [-500,499], b = [-500,499]; input:
	
    int res, cnt;
    res = a;
    cnt = b;
	
    while (cnt > 0) {
	cnt = cnt - 1;
	res = res + 1;
    }
	
    assert(res==(a + b));
    return 0;
}
