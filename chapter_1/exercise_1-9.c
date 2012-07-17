#include <stdio.h>

/* Run this program on itself (this file) and the following string "    " 
 * will be only one blank long.
 */

main ()

{
	int	c; 

	while ((c = getchar()) != EOF) {

		if (c == ' ') {

			putchar(' ');
			while ((c = getchar()) != EOF && c == ' ')

				;
	
		}
		if (c != EOF)

			putchar(c);

	}
}
