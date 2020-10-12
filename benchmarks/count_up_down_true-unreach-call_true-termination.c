int testfun(int n)
{
  __counterSharp_assume(n >= -5 && n <= 4);
  int x=n, y=0;
  while(x>0)
  {
    x--;
    y++;
  }
  __counterSharp_assert(y==n);
}