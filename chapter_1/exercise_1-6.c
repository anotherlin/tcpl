#include <stdio.h>

/* Press Ctrl-D (end of file) to obtain 0, or press any key and then <enter> 
 * for 1. 
 */

main ()

{
	int	c;

	c = getchar() != EOF;
	printf("c = getchar() != EOF is %d\n", c);
}
