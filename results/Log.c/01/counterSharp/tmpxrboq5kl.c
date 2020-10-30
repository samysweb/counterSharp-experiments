char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int x)
{
  int __counterSharp_returnVal;
  if (!((x >= 0) && (x <= 9)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int xtmp;
  int res;
  int restmp;
  res = 0;
  while (x > 1)
  {
    xtmp = x;
    restmp = 0;
    while (xtmp > 1)
    {
      xtmp = xtmp - 2;
      restmp = restmp + 1;
    }

    x = xtmp;
    res = res + 1;
  }

  if (!(res <= 5))
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


