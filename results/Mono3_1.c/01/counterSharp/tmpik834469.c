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

  int y = 0;
  while (x < 1000000)
  {
    if (x < 500000)
    {
      y++;
    }
    else
    {
      y--;
    }

    x++;
  }

  if (!(y != 0))
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


