char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int y)
{
  int __counterSharp_returnVal;
  if (!((y >= (-5)) && (y <= 4)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int LARGE_INT = 1000000;
  int x;
  x = -50;
  while (x < 0)
  {
    x = x + y;
    y++;
  }

  if (!(y > 0))
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


