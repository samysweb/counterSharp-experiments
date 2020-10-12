int testfun(int x) {
  __counterSharp_assume(x>=0&&x<=9);
  int y = 0;
  while (x < 1000000) {
    if (x<500000) {
	y++;
    } else {
	y--;
    }
	x++;
  }
  __counterSharp_assert(y!=0);
}
