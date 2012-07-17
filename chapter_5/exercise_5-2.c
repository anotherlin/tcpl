#include <ctype.h>
#include <stdio.h>

/* getfloat() uses the same return values as getint(). */

int 	getfloat (double *pf);

int main ()

{
	for ( ; ; ) {

		int	r;
		double	f;

		if ((r = getfloat(&f)) == EOF)

			return 0;

		else if (r != 0)

			printf("%f\n", f);

	}
}

int	getch (void);
void	ungetch (int c);

int getfloat (double *pf)

{
	int	c, sign;
	double	val, power;

	while (isspace(c = getch()))

		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {

		ungetch(c);
		return 0;

	}

	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')

		if (!isdigit(c = getch()) && c != '.') {

			ungetch(c);
			return 0;

		}

	if (c == '.') {

		ungetch(c = getch());
		if (!isdigit(c))

			return 0;

		else

			c = '.';

	}

	for (val = 0.0; isdigit(c); c = getch())

		val = 10.0 * val + (c - '0');

	if (c == '.')

		c = getch();

	for (power = 1.0; isdigit(c); c = getch()) {

		val = 10.0 * val + (c - '0');
		power *= 10.0;

	}
	*pf = sign * val / power;

	if (c != EOF)

		ungetch(c);

	return c;
}

#define BUFSIZE	100

char	buf[BUFSIZE];
int	bufp = 0;

int getch (void)

{
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch (int c)

{
	if (bufp >= BUFSIZE)

		printf("ungetch(): Too many characters!\n");

	else

		buf[bufp++] = c;
}
