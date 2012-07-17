#include <stdio.h>

void 	entab (int n);

int main () 

{
	entab(8);
	return 0;
}

void entab (int n)

{
	int	column, blanks, c;
	
	column = blanks = 0;
	while ((c = getchar()) != EOF) {

		if (c == ' ')
		
			blanks++;
			
		else if (c == '\t')
	
			blanks = blanks + n - (column + blanks) % n;

		else {

			while (blanks) {

				int	t;

				t = n - column % n;

				/* If either a tab or a single blank can be
 				 * be used to reach a tab stop, a blank is
				 * used because this would make the output
				 * more robust if read with a different tab
				 * size.
				 */
  
				if (t <= blanks && t != 1) {

					column = column + t;
					putchar('\t');
					blanks = blanks - t;
				
				} else
						
					do {
					
						column++;
						putchar(' ');
						
					} while (--blanks);
			
			}
			putchar(c);
			if (c == '\n')
			
				column = 0;
			
			else
			
				column++;
		
		}
	
	}
}
