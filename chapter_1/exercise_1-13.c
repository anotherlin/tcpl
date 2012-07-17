#include <stdio.h>

/* A word is any consecutive sequence of letter(s).  There is a maximum length
 * for words (too long ones are ignored) but no limit for the number of words.
 */

#define MAXIMUM_LENGTH	9

main ()

{
	int	i, counts[MAXIMUM_LENGTH], 
		is_in_word, 
		length, max, 
		c;

	/* Count words. */

	for (i = 0; i < MAXIMUM_LENGTH; i++)

		counts[i] = 0;

	is_in_word = length = max = 0;
	while ((c = getchar()) != EOF)

		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {

			is_in_word = 1;
			length++;

		} else {

			if (is_in_word && length <= MAXIMUM_LENGTH)

				if (++counts[length - 1] > max)

					max = counts[length - 1];

			is_in_word = length = 0;

		}

	/* Print horizontal histogram. */
	
	for (i = 0; i < MAXIMUM_LENGTH; i++) {

		printf("%2d: ", i + 1);
		c = counts[i];
		while (c-- != 0)

			putchar('=');

		putchar('\n');

	}

	/* Print vertical histogram. */

	while (max > 0) {

		for (i = 0; i < MAXIMUM_LENGTH; i++)

			if (counts[i] >= max)

				printf(" | ");

			else

				printf("   ");

		putchar('\n');
		max--;

	}
	for (i = 0; i < MAXIMUM_LENGTH; i++)
	
		printf("%2d ", i + 1);

	putchar('\n');
}
