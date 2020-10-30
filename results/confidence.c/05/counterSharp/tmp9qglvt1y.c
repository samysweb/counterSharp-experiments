char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int testfun(int someInput)
{
  int __counterSharp_returnVal;
  if (!(someInput > 0))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int sum = 0;
  if ((someInput >> 8) == 0)
  {
    for (int i = 1; i <= someInput; i++)
    {
      if ((someInput >> 7) == 0)
        sum += i;

    }

  }

  if (!((someInput >= 256) || (((someInput * (someInput + 1)) / 2) == sum)))
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


