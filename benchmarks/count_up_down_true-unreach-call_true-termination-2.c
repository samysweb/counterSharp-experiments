int testfun(int n)
{
  __counterSharp_assume(n >= -500 && n <= 499);
  int x=n, y=0;
  while(x>0)
  {
    x--;
    y++;
  }
  __counterSharp_assert(y==n);
}