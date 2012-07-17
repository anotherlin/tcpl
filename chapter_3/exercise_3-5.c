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

void itob (int n, char s[], int b)

{
	int	i, sign;

	if ((sign = n) < 0)

		n = -n;

	/* Letters are used if the chosen base is greater than 10, this works
	 * up to base 36.  The base must be greater or equal to 2 but this is
	 * not checked.
	 */

	i = 0;
	do {

		s[i] = n % b;
		s[i] += s[i] < 10 ? '0' : 'a' - 10;
		i++;

	} while ((n /= b) > 0);
	if (sign < 0)

		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

#define BUFFER_SIZE	16
#define TEST_VALUE	246810

int main ()

{
	char	s[BUFFER_SIZE];

	itob(TEST_VALUE, s, 16);
	printf("TEST_VALUE = 0x%s (0x%x)\n", s, TEST_VALUE);

	return 0;
}
