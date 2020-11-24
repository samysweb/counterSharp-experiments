char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int x1)
{
  int __counterSharp_returnVal;
  if (!(x1 > (-1073741824)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  if (x1 < 0)
  {
    x1 -= 1073741824;
  }
  else
  {
    x1 += 1073741824;
  }

  if (!(x1 < 0))
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


