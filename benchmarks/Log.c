int testfun(int x) {
	__counterSharp_assume(x>=0&&x<=9);
    int xtmp;
    int res;
    int restmp;

    res = 0;
    while (x > 1) {
        xtmp = x;
        restmp = 0;
        while (xtmp > 1) {
            xtmp = xtmp-2;
            restmp = restmp+1;
        }
        x = xtmp;
        res = res+1;
    }
    __counterSharp_assert(res<=5);
    return 0;
}
