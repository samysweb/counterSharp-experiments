char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
int usqrt(int x)
{
  int __counterSharp_returnVal;
  if (!(x >= 0))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  int input = x;
  int a = 0;
  int r = 0;
  int e = 0;
  for (int i = 0; i < 32; i++)
  {
    r = (r << 2) + ((x & (3L << (32 - 2))) >> (32 - 2));
    x <<= 2;
    a <<= 1;
    e = (a << 1) + 1;
    if (r >= e)
    {
      r -= e;
      a++;
    }

  }

  int lower = a >> 16;
  unsigned int upper = lower + 1;
  if (!(((lower * lower) <= input) && ((upper * upper) > input)))
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  {
    __counterSharp_returnVal = a;
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


