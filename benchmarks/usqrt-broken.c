/* usqrt:
    ENTRY x: unsigned long
    EXIT  returns floor(sqrt(x) * pow(2, BITSPERINT/2))

    Since the square root never uses more than half the bits
    of the input, we use the other half of the bits to contain
    extra bits of precision after the binary point.

    EXAMPLE
        suppose BITSPERINT = 32
        then    usqrt(144) = 786432 = 12 * 65536
                usqrt(32) = 370727 = 5.66 * 65536

    NOTES
        (1) change BITSPERINT to BITSPERINT/2 if you do not want
            the answer scaled.  Indeed, if you want n bits of
            precision after the binary point, use BITSPERINT/2+n.
            The code assumes that BITSPERINT is even.
        (2) This is really better off being written in assembly.
            The line marked below is really a "arithmetic shift left"
            on the double-long value with r in the upper half
            and x in the lower half.  This operation is typically
            expressible in only one or two assembly instructions.
        (3) Unrolling this loop is probably not a bad idea.

    ALGORITHM
        The calculations are the base-two analogue of the square
        root algorithm we all learned in grammar school.  Since we're
        in base 2, there is only one nontrivial trial multiplier.

        Notice that absolutely no multiplications or divisions are performed.
        This means it'll be fast on a wide range of processors.
*/

#define BITSPERINT 32

#define TOP2BITS(x) ((x & (3L << (BITSPERINT-2))) >> (BITSPERINT-2))
int usqrt(int x) {
	__counterSharp_assume(x>=0);
	int input = x;
	int a = 0, r = 0, e = 0;
	for (int i = 0; i < 32; i++) {
		r = (r << 2) + TOP2BITS(x);
		x <<= 2; /* NOTE 2 */
		a <<= 1;
		e = (a << 1) + 1;
		if (r >= e) {
			r -= e;
			a++;
		}
	}
	int lower = (a>>16);
	unsigned int upper = lower+1;
	__counterSharp_assert(lower*lower<=input
		&& upper*upper>input);
	return a;
}