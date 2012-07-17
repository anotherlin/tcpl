#include <stdio.h>

/* See note in exercise 2-6. */

unsigned invert (unsigned x, int p, int n)

{
	return x ^ (~(~0 << n) << (p + 1 - n));
}

int main ()

{
	unsigned	x;
	int		p, n;

	x = 0xaa;
	p = 5;
	n = 4;
	printf("invert(0x%x, %d, %d) = 0x%x\n", x, p, n, invert(x, p, n));

	return 0;
}
