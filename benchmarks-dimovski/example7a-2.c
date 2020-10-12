
// this is also nice example to explain in journal version 

int main() {
  int x=[0,999], y=[0,999]; input:
	
  while (x >= 0) {  
    x = x - 1;
	y = y + 1;
  }
	
  assert (y>=1000);
  return 0;
}