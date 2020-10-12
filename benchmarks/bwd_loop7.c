extern unsigned char nondetChar();
int testfun(int j)
{
  __counterSharp_assume(j >= 0 && j <= 9);
  int i = 0;
  while (i < 100) {
    i++;
	int tmp = (nondetChar() % 2);
    j = j + tmp;
  }
  __counterSharp_assert(j <= 105);
  return 0; 
}
