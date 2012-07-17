#include <stdio.h>
#include <string.h>

#define MAXLINE	1000
	
int 	getline (char line[], int max);
int 	strrindex (char s[], char t[]);

/* Run this program on itself and it will print the next statement with the 
 * index of the pattern inside comment (second one, rightmost). 
 */

char 	pattern[] = "ould";	/* Pattern "ould". */

int main ()

{
	char	line[MAXLINE];
	int	found = 0, i;

	while (getline(line, MAXLINE) > 0)

		if ((i = strrindex(line, pattern)) >= 0) {

			printf("%d:\t%s", i, line);
			found++;

		}

	return found;
}

int getline (char s[], int lim)

{
	int	c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')

		s[i++] = c;

	if (c == '\n')

		s[i++] = c;

	s[i] = '\0';

	return i;
}

int strrindex (char s[], char t[])

{
	int	i, j, k;

	for (i = strlen(s) - 1; i >= 0; i--) 

		for (j = i, k = strlen(t) - 1; 
			j >= 0 && k >= 0 && s[j] == t[k]; 
			j--, k--)

			if (k == 0)

				return j;

	return -1;
}
