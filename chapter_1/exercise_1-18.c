#include <stdio.h>

/* This program works only if lines are short enough so that they end with a
 * newline character when read by getline().  As MAXLINE is a huge number, this
 * shoudn't be a problem here.
 */

#define MAXLINE	1000

int 	getline (char line[], int limit);

int main ()

{
	int	len;
	char	line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0) {

		len = len - 2;
		if (len >= 0 && line[len] == '\n')

			len--;

		while (len >= 0 && (line[len] == ' ' || line[len] == '\t'))

			len--;

		if (len >= 0) {

			line[len + 1] = '\n';
			line[len + 2] = '\0';
			printf("%s", line);

		}

	}

	return 0;
}

int getline (char line[], int limit)

{
	int	i, c;

	for (i = 0; 
		i < limit - 1 && (c = getchar()) != EOF && c != '\n'; 
		i++)

		line[i] = c;

	if (c == '\n') {

		line[i] = c;
		i++;

	}
	line[i] = '\0';

	return i;
}
