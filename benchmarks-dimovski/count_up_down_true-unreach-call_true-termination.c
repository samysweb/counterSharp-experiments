extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: __VERIFIER_error();
  }
  return;
}


int main()
{
  int n = [-5,4]; input:
	
  int x=n, y=0;
  while(x>0)
  {
    x--;
    y++;
  }
  assert(y==n);
}

