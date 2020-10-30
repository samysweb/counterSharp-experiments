char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
extern unsigned char nondetChar();
int testfun(int j)
{
  int __counterSharp_returnVal;
  if (!((j >= 0) && (j <= 9)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int i = 0;
  while (i < 100)
  {
    i++;
    int tmp = nondetChar() % 2;
    if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
      goto __counterSharp_end;

    j = j + tmp;
  }

  if (!(j <= 105))
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  {
    __counterSharp_returnVal = 0;
    __counterSharp_end:
    {
      __CPROVER_assert((__counterSharp_assertMiss != 0) || (__counterSharp_assumeMiss != 0), "");
      __CPROVER_assert((__counterSharp_assertMiss != 1) || (__counterSharp_assumeMiss != 0), "");
      __CPROVER_assert(__counterSharp_assumeMiss != 0, "");
      __CPROVER_assert(__counterSharp_assumeMiss != 1, "");
      return __counterSharp_returnVal;
    }

  }
}


