#include <stdio.h>

/* Here, a word is any consecutive sequence of letter(s). */

main ()

{
	int	is_in_word, c;

	is_in_word = 0;
	while ((c = getchar()) != EOF)

		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {

			is_in_word = 1;
			putchar(c);

		} else {

			if (is_in_word)

				putchar('\n');

			is_in_word = 0;

		}
}
