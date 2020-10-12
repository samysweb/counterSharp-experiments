// parametric loops: true for all positive n


void main()
{
  int j = [-500,499]; input:
	
  int n = 0; 
  n = [0,32767];
  int i = 0;

    while (i < n) {
      i++;
      j = j + 1;
    }
	
    assert(j <= n + 5);

}
