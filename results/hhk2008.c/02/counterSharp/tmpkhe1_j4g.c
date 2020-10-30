char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int a, int b)
{
  int __counterSharp_returnVal;
  if (!((((a >= (-5)) && (a <= 4)) && (b >= (-5))) && (b <= 4)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int res;
  int cnt;
  res = a;
  cnt = b;
  while (cnt > 0)
  {
    cnt = cnt - 1;
    res = res + 1;
  }

  if (!(res == (a + b)))
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


