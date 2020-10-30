char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int n)
{
  int __counterSharp_returnVal;
  if (!((n >= (-5)) && (n <= 4)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int x = n;
  int y = 0;
  while (x > 0)
  {
    x--;
    y++;
  }

  if (!(y == n))
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


