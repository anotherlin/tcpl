#include <stdio.h>

/* Use a short maximum length to force lines to be displayed cut.  */

#define MAXLINE	20

int 	getline (char line[], int limit);
void	copy (char to[], char from[]);

int main ()

{
	int	len;
	int	max;
	char	line[MAXLINE];
	char	longest[MAXLINE];

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)

		if (len > max) {

			max = len;
			copy(longest, line);

		}

	if (max > 0)

		printf("Longest line is %d characters:\n%s", max, longest);

	return 0;
}

int getline (char line[], int limit)

{
	int	i, c;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)

		if (i < limit - 2)

			line[i] = c;

	/* Make sure that the returned string ends with a newline character and
	 * is null terminated.
 	 */

	if (i < limit - 1) {

		line[i] = '\n';
		line[i + 1] = '\0';

	} else {

		line[limit - 2] = '\n';
		line[limit - 1] = '\0';

	}

	/* A newline counts as one character, adjust length if needed. */

	if (c == '\n')

		i++;

	return i;
}

void copy (char to[], char from[])

{
	int	i;

	i = 0;
	while ((to[i] = from[i]) != '\0')

		i++;
}
