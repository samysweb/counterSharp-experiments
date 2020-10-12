int testfun(int y) {
	__counterSharp_assume(y>=-5&&y<=4);
	int LARGE_INT = 1000000;
    int x;
    x = -50;
    while (x < 0) {
	x = x + y;
	y++;
    }
    __counterSharp_assert(y > 0);
    return 0;
}
