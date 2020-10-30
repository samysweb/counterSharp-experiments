char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int j)
{
  int __counterSharp_returnVal;
  if (!((j >= 0) && (j <= 999)))
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
    j++;
  }

  if (!(j <= 105))
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


