#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* By default, tab stops are placed every 8 columns and starts at column 0. 
 * The input is supposed to use the default tab setting.
 */

#define DEFAULT_START_COLUMN    0
#define DEFAULT_TABSIZE         8

void 	entab (int m, int n);

int main (int argc, char *argv[])

{
        int     m, n;

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

	entab(m, n);

	return 0;
}

void entab (int m, int n)

{
	int	column, blanks, c;
	
	column = blanks = 0;
	while ((c = getchar()) != EOF) {

		if (c == ' ')
		
			blanks++;
			
		else if (c == '\t')

			blanks += n - (column + blanks) % n;

		else {

			while (blanks) {

				int	t;

				if (column < m)

					t = m - column;

				else

					t = n - (column - m) % n;

				if (t <= blanks) {

					column += t;
					putchar('\t');
					blanks -= t;
				
				} else {
						
					do {
					
						column++;
						putchar(' ');
						
					} while (--blanks);
					break;

				}

			}
			putchar(c);
			column = c == '\n' ? 0 : column + 1;
		
		}
	
	}
}
