char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
extern unsigned char undetChar();
int testfun(int x, int y)
{
  int __counterSharp_returnVal;
  if (!((((x >= 0) && (x <= 9)) && (y >= 0)) && (y <= 9)))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  while (x >= 0)
  {
    x = x - 1;
    y = y + ((undetChar() % 3) - 1);
    if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
      goto __counterSharp_end;

  }

  if (!(y > 5))
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


