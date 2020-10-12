int testfun(int a, int b) {
	__counterSharp_assume(a>=-5&&a<=4&&b>=-5&&b<=4);
    int res, cnt;
    res = a;
    cnt = b;
    while (cnt > 0) {
	cnt = cnt - 1;
	res = res + 1;
    }
    __counterSharp_assert(res==(a + b));
    return 0;
}