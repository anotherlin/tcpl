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

void itoa (int n, char s[], int w)

{
	int	i, sign;

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

	w -= i;
	while (w-- > 0)

		s[i++] = ' ';

	s[i] = '\0';
	reverse(s);
}

#define BUFFER_SIZE	16

int main ()

{
	char	s[BUFFER_SIZE];

	itoa(INT_MIN, s, BUFFER_SIZE - 1);
	printf("INT_MIN = %s\n", s);

	return 0;
}
