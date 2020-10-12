extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }

int main(void) {
  int x = [0,9]; input: 
  int y = 0;
  while (x < 1000000) {
    if (x<500000) {
	y++;
    } else {
	y--;
    }
	x++;
  }
  assert(y!=0);
}
