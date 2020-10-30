char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
extern int nondetInt();
int testfun(int n)
{
  int __counterSharp_returnVal;
  if (!((n >= 0) && (n <= 999)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int i = 0;
  int x = 0;
  int y = 0;
  for (i = 0; i < n; i++)
  {
    x = x - y;
    y = nondetInt();
    if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
      goto __counterSharp_end;

    x = x + y;
  }

  if (!(x == 0))
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


