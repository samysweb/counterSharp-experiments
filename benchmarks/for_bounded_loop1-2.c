extern int nondetInt();
int testfun(int n) {
	__counterSharp_assume(n>=0&&n<=999);
  int i=0, x=0, y=0;
  for(i=0; i<n; i++)
  {
    x = x-y;
    y = nondetInt();
    x = x+y;
  }
  __counterSharp_assert(x==0);
}

