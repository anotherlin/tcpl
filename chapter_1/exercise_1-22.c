#include <stdio.h>

/* The idea is to accumulate non-blank characters in a buffer until a blank or 
 * newline is reached.  The accumulated characters are then written if there 
 * is enough space, otherwise they are "folded" into a new line.  To simplify 
 * code, a buffer of FOLDING_LENGTH size is used.
 */

#define FOLDING_LENGTH	60

void 	fold (int tab_size);
void	print_buffer (char buffer[], int length);

int main ()

{
	fold(8);
	return 0;
}

void fold (int tab_size)

{
	int	column, non_blanks, c;
	char	buffer[FOLDING_LENGTH];
	
	column = non_blanks = 0;
	while ((c = getchar()) != EOF)

		if (c == ' ' || c == '\t') {

			if (column + non_blanks < FOLDING_LENGTH) {

				print_buffer(buffer, non_blanks);
				column = column + non_blanks;

			} else {
			
				putchar('\n');
				print_buffer(buffer, non_blanks);
				column = non_blanks;

			}
			non_blanks = 0;
			
			putchar(c);
			if (c == '\t')

				column = column + tab_size - column % tab_size;

			else

				column++;
			
			if (column > FOLDING_LENGTH - 1) {

				putchar('\n');
				column = 0;

			}

		} else if (c == '\n') {

			if (column + non_blanks >= FOLDING_LENGTH)

				putchar('\n');

			print_buffer(buffer, non_blanks);
			putchar('\n');
			column = non_blanks = 0;

		} else if (non_blanks < FOLDING_LENGTH)

			buffer[non_blanks++] = c;

		else {

			/* Handle read buffer overflows.  */

			if (column != 0)

				putchar('\n');

			print_buffer(buffer, FOLDING_LENGTH);

			do 

				putchar(c);

			while ((c = getchar()) != EOF 
			&& c != ' ' && c != '\t' && c != '\n');

			putchar('\n');

			column = non_blanks = 0;

		}
}

void print_buffer (char buffer[], int length)

{
	int	i;

	for (i = 0; i < length; i++) 

		putchar(buffer[i]);
}
