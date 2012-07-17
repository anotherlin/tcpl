#include <stdio.h>
#include <limits.h>
#include <float.h>

/* This program must be compiled with floating-point optimizations turned off,
 * otherwise the results may be wrong depending on the processor and compiler.
 *
 * You may also want to take a look at Steven Pemberton's enquire.c, available 
 * at http://homepages.cwl.nl/~steven/enquire.html.  It is a small C program 
 * that determines many properties of the C compiler and the machine on which
 * it runs.
 */

int main ()

{
	long	l;
	int	i, j, k, m;
	float	f, g, h;

	/* Compute maximum and minimum for a long, the computer is assumed to
	 * use two's complement format to represent integers. 
	 */
	
	l = 1;
	while (2 * l + 1 > l) 
	
		l = 2 * l + 1;
		
	printf("LONG_MAX: %ld (%ld)\n", l, LONG_MAX);
	printf("LONG_MIN: %ld (%ld)\n", -l - 1, LONG_MIN);

	/* Compute maximum and minimum exponents for a float.  This code will
	 * also works for double or long double, as long as floating-point
	 * numbers are represented in IEEE754 "basic" or "extended" formats.
 	 */

	i = 0;
	f = 1.0f;
	while (f * 2.0f != f) {
			
		i++;
		f = f * 2.0f;
		
	}
	printf("FLT_MAX_EXP: %d (%d)\n", i, FLT_MAX_EXP);
	printf("FLT_MIN_EXP: %d (%d)\n", -i + 3, FLT_MIN_EXP);

	/* Compute maximum non-infinite float and find the number of bits of
	 * the significand at the same time. 
	 */

	f = 1.0f;
	for (j = 1; j < i; j++)

		f = f * 2.0f;

	j = i;
	m = 0;
	g = f;
	for ( ; ; ) {

		j--;
		h = 1.0f;
		for (k = 1; k < j; k++)

			h = h * 2.0f;

		if (g + h == g)

			break;

		f = g;
		g = g + h;
		m++;	

	} 

	printf("FLT_MAX: %g (%g)\n", f, FLT_MAX);

	/* Compute minimum non-denormalized float, which is 1e-FLT_MIN_EXP. */

	f = 1.0f;
	for (j = 0; j < i - 2; j++)

		f = f / 2.0f;

	printf("FLT_MIN: %g (%g)\n", f, FLT_MIN);

	/* Compute the smallest epsilon such as 1.0f + epsilon != 1.0f, which 
	 * is 1e-(the number of bits of the significand). 
	 */

	f = 1.0f;
	for (i = 0; i < m - 1; i++)

		f = f / 2.0f;

	printf("FLT_EPSILON: %g (%g)\n", f, FLT_EPSILON);

	return 0;
}
