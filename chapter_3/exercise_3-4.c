#include <limits.h>
#include <stdio.h>
#include <string.h>

void reverse (char s[])

{
	int	c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {

		c = s[i];
		s[i] = s[j];
		s[j] = c;

	}
}

void itoa (int n, char s[])

{
	int	i, sign;

	/* In two's complement, the smallest int cannot be represented if 
	 * negated because it would be INT_MAX + 1.  We handle it as a special
	 * case, this is just arithmetic.
	 */

	i = 0;
	if ((sign = n) < 0) {

		if (n == INT_MIN) {

			n = -(n + 1);
			s[i++] = n % 10 + 1 + '0';
			n /= 10;

		} else

			n = -n;

	}
	do 

		s[i++] = n % 10 + '0';

	while ((n /= 10) > 0);
	if (sign < 0)

		s[i++] = '-';

	s[i] = '\0';
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
