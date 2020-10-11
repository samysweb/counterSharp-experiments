/**
 * This benchmark fails for any input in the interval [128,255].
 * When examining this benchmark with a bound of 100,
 * we will not detect this behaviour and have a confidence gap of 156 (all numbers in [101,255]).
 */
int testfun(int someInput) {
	__counterSharp_assume(someInput>0);
	int sum = 0;
	if ((someInput>>8) == 0) {
		for (int i=1; i<=someInput; i++) {
			if ((someInput>>7) == 0) sum+=i;
		}
	}
	__counterSharp_assert(someInput>=256 || (someInput*(someInput+1))/2==sum);
}