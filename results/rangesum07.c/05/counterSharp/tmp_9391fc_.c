char __counterSharp_assumeMiss = 0;
char __counterSharp_assertMiss = 0;
extern void abort(void);
void reach_error()
{
  if (!0)
  {
    __counterSharp_assertMiss = 1;
    goto __counterSharp_end;
  }
  else
    ;

  __counterSharp_end:
  {
    return;
  }

}

extern int __VERIFIER_nondet_int();
void init_nondet(int x[7])
{
  int i;
  for (i = 0; i < 7; i++)
  {
    x[i] = __VERIFIER_nondet_int();
    if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
      goto __counterSharp_end;

  }

  __counterSharp_end:
  {
    return;
  }

}

int rangesum(int x[7])
{
  int __counterSharp_returnVal;
  int i;
  long long ret;
  ret = 0;
  int cnt = 0;
  for (i = 0; i < 7; i++)
  {
    if (i > (7 / 2))
    {
      ret = ret + x[i];
      cnt = cnt + 1;
    }

  }

  if (cnt != 0)
  {
    __counterSharp_returnVal = ret / cnt;
    __counterSharp_end:
    {
      return __counterSharp_returnVal;
    }

  }
  else
  {
    __counterSharp_returnVal = 0;
    goto __counterSharp_end;
  }

}

int testfun(int x1, int x2, int x3, int x4, int x5, int x6, int x7)
{
  int __counterSharp_returnVal;
  int x[7];
  x[0] = x1;
  x[1] = x2;
  x[2] = x3;
  x[3] = x4;
  x[4] = x5;
  x[5] = x6;
  x[6] = x7;
  int temp;
  int ret;
  int ret2;
  int ret5;
  ret = rangesum(x);
  if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
    goto __counterSharp_end;

  temp = x[0];
  x[0] = x[1];
  x[1] = temp;
  ret2 = rangesum(x);
  if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
    goto __counterSharp_end;

  temp = x[0];
  for (int i = 0; i < (7 - 1); i++)
  {
    x[i] = x[i + 1];
  }

  x[7 - 1] = temp;
  ret5 = rangesum(x);
  if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
    goto __counterSharp_end;

  if ((ret != ret2) || (ret != ret5))
  {
    {
      reach_error();
      if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
        goto __counterSharp_end;

      abort();
      if ((__counterSharp_assertMiss == 1) || (__counterSharp_assumeMiss == 1))
        goto __counterSharp_end;

    }
  }

  {
    __counterSharp_returnVal = 1;
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


