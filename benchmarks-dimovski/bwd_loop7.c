// loop with assert at exit and non-deterministic body



int main()
{
  int j = [0,9]; input:
	
  int i = 0;
	
  while (i < 100) {
    i++;
    j = j + [0,1];
  }
	
  assert(j <= 105);
  return 0; 
}
