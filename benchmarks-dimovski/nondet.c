int main() {
  int x = [-2147483648,2147483647]; input:
	if (x<0) {
		x=0;
	}
	int y = [-2147483648,2147483647];
	int div = y * x;
	assert(div!=0);
	return 100/div;
}
