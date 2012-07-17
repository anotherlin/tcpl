#include <stdio.h>

int bitcount (unsigned x)

{
	int	b;

	/* The borrow of the substraction will carry until the rightmost 1-bit
	 * and clear it.  It won't change any of the bits left to it, which is 
	 * useful here.
	 */

	for (b = 0; x != 0; x &= (x - 1))

		b++;
	
	return b;
}

int main ()

{
	int	x = 0x3e;

	printf("bitcount(0x%x) = %d\n", x, bitcount(x));
	
	return 0;
}
