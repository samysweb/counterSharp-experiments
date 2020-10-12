int testfun(int j)
{
  __counterSharp_assume(j >= 0 && j <= 999);
  int i = 0;
  while (i < 100) {
    i++;
    j++;
  }
  __counterSharp_assert(j <= 105);
}
