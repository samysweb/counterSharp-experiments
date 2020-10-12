// Source: Sumit Gulwani, Saurabh Srivastava, Ramarathnam Venkatesan: "Program
// Analysis as Constraint Solving", PLDI 2008.

#include "assert.h"
int main() {
	int y = [-49,950]; input:
	int LARGE_INT = 1000000;
    int x;
    x = -50;
			
	
    while (x < 0) {
	x = x + y;
	y++;
    }
	
    assert(y > 0);
    return 0;
}
