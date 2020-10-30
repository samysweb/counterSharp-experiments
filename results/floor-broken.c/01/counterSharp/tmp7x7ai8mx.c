char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
;
#include <math.h>
long double testfun(long double a)
{
  long double __counterSharp_returnVal;
  if (!(((a >= 0.0) && (!isnan(a))) && (!isinf(a))))
  {
    __counterSharp_assumeMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  long double a0;
  int e;
  int n;
  a0 = a;
  e = ((int *) (&a))[4] & 0x7FFF;
  if (e == 0)
  {
    __counterSharp_returnVal = (long double) 0.0;
    __counterSharp_end:
    {
      __CPROVER_assert((__counterSharp_assertMiss != 0) || (__counterSharp_assumeMiss != 0), "");
      __CPROVER_assert((__counterSharp_assertMiss != 1) || (__counterSharp_assumeMiss != 0), "");
      __CPROVER_assert(__counterSharp_assumeMiss != 0, "");
      __CPROVER_assert(__counterSharp_assumeMiss != 1, "");
      return __counterSharp_returnVal;
    }

  }

  e -= 16383;
  if (e < 0)
  {
    a = 0.0;
  }
  else
    if ((n = 63 - e) > 0)
  {
    if (n < 32)
    {
      ((unsigned long *) (&a))[0] = (1L << n) - 1;
    }
    else
    {
      ((unsigned long *) (&a))[0] = 0;
      n -= 32;
      if (n)
      {
        ((unsigned long *) (&a))[1] = (1L << n) - 1;
      }

    }

  }


  if ((a0 < 0) && (a0 != a))
    a -= 1.0;

  if (!(a0 >= a))
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  {
    __counterSharp_returnVal = a;
    goto __counterSharp_end;
  }
}


