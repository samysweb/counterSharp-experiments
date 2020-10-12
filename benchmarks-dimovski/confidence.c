void main() {
  int someInput = [0,2147483647]; input:
	int sum = 0;
	if (someInput/256 == 0) {
		for (int i=1; i<=someInput; i++) {
			if (someInput/128 == 0) sum+=i;
		}
	}
	assert(someInput>=256 || (someInput*(someInput+1))/2==sum);
}