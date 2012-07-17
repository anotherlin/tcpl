#include <ctype.h>
#include <stdio.h>

int 	getint (int *pn);

int main ()

{
	for ( ; ; ) {

		int	r, n;

		if ((r = getint(&n)) == EOF)

			return 0;

		else if (r != 0)

			printf("%d\n", n);

	}
}

int	getch (void);
void	ungetch (int c);

int getint (int *pn)

{
	int	c, sign;

	while (isspace(c = getch()))

		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {

		ungetch(c);
		return 0;

	}

	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')

		if (!isdigit(c = getch())) {

			ungetch(c);
			return 0;

		}

	for (*pn = 0; isdigit(c); c = getch())

		*pn = 10 * *pn + c - '0';

	*pn *= sign;

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
