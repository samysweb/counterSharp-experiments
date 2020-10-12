int testfun(int i)
{
  __counterSharp_assume(i >= 0 && i <= 999);
  while (i < 100) {
    i++;
  }
  __counterSharp_assert(i<=101);
  return 0;
}