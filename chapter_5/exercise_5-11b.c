#include <stdio.h>
#include <stdlib.h>

/* See explanations in exercise_5-11a.c. */

#define MAXSTOPS	100
#define DEFAULT_TABSIZE	8

void 	detab (int nstops, int stops[], int m, int n);
	
int main (int argc, char *argv[])

{
	int	nstops, stops[MAXSTOPS];

	argc--;
	argv++;
	for (nstops = 0; nstops < MAXSTOPS && nstops < argc; nstops++)

		stops[nstops] = atoi(argv[nstops]);

	detab(nstops, stops, nstops ? stops[nstops - 1] : 0, DEFAULT_TABSIZE);

	return 0;
}

void detab (int nstops, int stops[], int m, int n)

{
	int	column, stop, c;

	column = stop = 0;
	while ((c = getchar()) != EOF)

		if (c == '\t')

			for ( ; ; ) {

				putchar(' ');
				column++;
				if (stop < nstops) {

					if (column == stops[stop]) {

						stop++;
						break;

					}

				} else if ((column - m) % n == 0)

					break;

			}

		else {

			putchar(c);
			if (c == '\n')
		
				column = stop = 0;

			else {

				column++;
				if (stop < nstops && column == stops[stop])

					stop++;

			}

		}
}
