// INT_MAX: 2147483647
// INT_MIN: -2147483648
int testfun(int x1) {
	__counterSharp_assume(x1 > -1073741824);
	if (x1 < 0) {
		x1 -= 1073741824;
	} else {
		x1 += 1073741824;
	}
	__counterSharp_assert(x1 < 0);
}