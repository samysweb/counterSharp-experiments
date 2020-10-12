extern unsigned int nondetInt();
int testfun(int j)
{
  __counterSharp_assume(j >= 0 && j <= 999);	
  int n = 0; 
  n = (nondetInt() % 32768);
  int i = 0;
    while (i < n) {
      i++;
      j = j + 1;
    }
    __counterSharp_assert(j <= n + 5);
}
