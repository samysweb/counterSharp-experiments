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
#include<malloc.h>
int testfun(int x)
{
  int __counterSharp_returnVal;
  if (x < 0)
  {
    x = 0;
  }

  int *y = malloc(sizeof(int));
  if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
    goto __counterSharp_end;

  int div = (*y) * x;
  if (!(div != 0))
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  {
    __counterSharp_returnVal = 100 / div;
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


