char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
extern unsigned int nondetInt();
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

  int n = 0;
  n = nondetInt() % 32768;
  if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
    goto __counterSharp_end;

  int i = 0;
  while (i < n)
  {
    i++;
    j = j + 1;
  }

  if (!(j <= (n + 5)))
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  __counterSharp_end:
  {
    __CPROVER_assert((__counterSharp_assertMiss != 0) || (__counterSharp_assumeMiss != 0), "");
    __CPROVER_assert((__counterSharp_assertMiss != 1) || (__counterSharp_assumeMiss != 0), "");
    __CPROVER_assert(__counterSharp_assumeMiss != 0, "");
    __CPROVER_assert(__counterSharp_assumeMiss != 1, "");
    return __counterSharp_returnVal;
  }

}


