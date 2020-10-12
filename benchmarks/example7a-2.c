int testfun(int x, int y) {
  __counterSharp_assume(x>=0&&x<=999&&y>=0&&y<=999);	
  while (x >= 0) {  
    x = x - 1;
	y = y + 1;
  }
  __counterSharp_assert(y>=1000);
  return 0;
}