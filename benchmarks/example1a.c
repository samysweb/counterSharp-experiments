int testfun(int x)
{
  __counterSharp_assume(x >= 0 && x <= 9);	
  while (x <= 100) 
    x = x + 1;
  __counterSharp_assert(x>=101);
  return 0;
}