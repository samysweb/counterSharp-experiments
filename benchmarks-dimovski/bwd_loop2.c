// loop with assert at exit


void main()
{
  int j = [0,9]; input:
  int i = 0;
	
  while (i < 100) {
    i++;
    j++;
  }
	
  assert(j <= 105);
}
