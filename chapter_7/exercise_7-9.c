#include <stdio.h>

/* The slow way is just to make comparisons. */

int isupper_slow (int c)

{
	return c >= 'A' && c <= 'Z';
}

/* The fast way is to use a table look-up.  c is supposed to have the value of
 * an unsigned char (0..255) or to be EOF (which we suppose is -1).
 */

int isupper_fast (int c)

{
	static const char isupper[257] = {

		0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	};
	
	return (isupper + 1)[c];
}

int main ()

{
	printf("isupper_slow(EOF) = %d.\n", isupper_slow(EOF));
	printf("isupper_fast(EOF) = %d.\n", isupper_fast(EOF));
	printf("isupper_slow('A') = %d.\n", isupper_slow('A'));
	printf("isupper_fast('A') = %d.\n", isupper_fast('A'));
	printf("isupper_slow('Z') = %d.\n", isupper_slow('Z'));
	printf("isupper_fast('Z') = %d.\n", isupper_fast('Z'));
	printf("isupper_slow('z') = %d.\n", isupper_slow('z'));
	printf("isupper_fast('z') = %d.\n", isupper_fast('z'));
	printf("isupper_slow('0') = %d.\n", isupper_slow('0'));
	printf("isupper_fast('0') = %d.\n", isupper_fast('0'));

	return 0; 
}
