int testfun(int x) {
	__counterSharp_assume(x>=-500&&x<=499);	
	while (x >= 0) {
		x = x - 1;
	}
	__counterSharp_assert(x>=-1);
	return 0;
}