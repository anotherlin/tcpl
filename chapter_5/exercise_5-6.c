#include <limits.h>
#include <stdio.h>

/* This is a rewrite of exercise 3-4 using pointers instead of array indexing.
 */

void reverse (char *s)

{
	char	*t;

	t = s;
	while (*t)

		t++;

	while (t >= s + 2) {

		int	c;

		c = *s;
		*s++ = *--t;
		*t = c; 

	}
}

void itoa (int n, char *s)

{
	char	*t; 
	int	sign;

	t = s;
	if ((sign = n) < 0) {

		if (n == INT_MIN) {

			n = -(n + 1);
			*t++ = n % 10 + 1 + '0';
			n /= 10;

		} else

			n = -n;

	}
	do 

		*t++ = n % 10 + '0';

	while ((n /= 10) > 0);
	if (sign < 0)

		*t++ = '-';

	*t = '\0';
	reverse(s);
}

#define BUFFER_SIZE	16

int main ()

{
	char	s[BUFFER_SIZE];

	itoa(INT_MIN, s);
	printf("INT_MIN = %s (%d)\n", s, INT_MIN);

	return 0;
}
