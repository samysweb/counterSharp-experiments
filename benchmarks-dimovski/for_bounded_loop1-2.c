

int main() {
  int n=[0,999]; input:

  int i=0, x=0, y=0;

  for(i=0; i<n; i++)
  {
    x = x-y;
    y = __VERIFIER_nondet_int();
    //if (y<=0) return 0;
    x = x+y;
  }
  assert(x==0);
}

