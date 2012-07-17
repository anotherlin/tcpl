#include <stdio.h>
#include <stdlib.h>

/* Use tab stops given as arguments or the default tab size otherwise.  The 
 * default tab size is also used after the last tab stop has been reached.  
 * The input is supposed to use the default tab size.
 */

#define MAXSTOPS	100
#define DEFAULT_TABSIZE	8

void 	entab (int nstops, int stops[], int m, int n);

int main (int argc, char *argv[]) 

{
	int     nstops, stops[MAXSTOPS];

	/* No error check on correctness of the tab stops. */

	argc--;
	argv++;
	for (nstops = 0; nstops < MAXSTOPS && nstops < argc; nstops++)

		stops[nstops] = atoi(argv[nstops]);

	entab(nstops, stops, nstops ? stops[nstops - 1] : 0, DEFAULT_TABSIZE);

	return 0;
}

void entab (int nstops, int stops[], int m, int n)

{
	int	column, blanks, stop, c;
	
	column = blanks = stop = 0;
	while ((c = getchar()) != EOF) {

		if (c == ' ')
		
			blanks++;
			
		else if (c == '\t')
		
			blanks += n - (column + blanks) % n;

		else {

			while (blanks) {

				int	t;

				if (stop < nstops)

					t = stops[stop] - column;

				else

					t = n - (column - m) % n;
  
				if (t <= blanks) {

					column += t;
					putchar('\t');
					blanks -= t;

					if (stop < nstops 
					&& column == stops[stop])
				
						stop++;

				} else {
						
					do {
					
						column++;
						putchar(' ');
						
					} while (--blanks);
					break;

				}

			}
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
}
