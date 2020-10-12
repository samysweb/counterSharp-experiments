/*
TERMINATION

suggested parameters:
- partition abstract domain = boxes [default]
- function abstract domain = affine [default]
- backward widening delay = 2 [default]
*/

int main() {
  int x=[0,999], y=[0,999]; input:
	
  while (x >= 0) {  
    x = x - 1;
	y = y + [-1,1];
  }
	
  assert (y>500);
  return 0;
}