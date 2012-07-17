#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* See explanations in exercise_5-12a.c. */

#define DEFAULT_START_COLUMN	0
#define DEFAULT_TABSIZE		8

void 	detab (int m, int n);

int main (int argc, char *argv[])

{
	int	m, n;

	m = DEFAULT_START_COLUMN;
	n = DEFAULT_TABSIZE;
	while (--argc > 0 && ((*++argv)[0] == '-' || *argv[0] == '+'))

		if (*argv[0] == '-') {

			if (isdigit(*++argv[0]))

				m = atoi(argv[0]);

		} else if (*argv[0] == '+') {

			if (isdigit(*++argv[0]))

				n = atoi(argv[0]);

		}

	detab(m, n);

	return 0;
}

void detab (int m, int n)

{
	int	column, c;

	column = 0;
	while ((c = getchar()) != EOF)

		if (c == '\t')

			for ( ; ; ) {

				putchar(' ');
				if (++column < m)

					continue;

				else if ((column - m) % n == 0)
	
					break;

			}

		else {

			putchar(c);
			column = c == '\n' ? 0 : column + 1;

		}
}
