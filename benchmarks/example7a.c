int testfun(int x, int y) {
  __counterSharp_assume(x>=0&&x<=9&&y>=0&&y<=9);	
  while (x >= 0) {  
    x = x - 1;
	y = y + 1;
  }
  __counterSharp_assert(y>=10);
  return 0;
}