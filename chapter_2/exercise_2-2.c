#include <stdio.h>

/* This is a somewhat simplified rewrite of exercise 1-16. */
 
#define MAXLINE	1000

int 	getline (char line[], int maxline);
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

		printf("%s", longest);

	return 0;
}

int getline (char s[], int lim)

{
	int	c, i;

	/* Logical expressions have value 0 for false or 1 for true, this fact
	 * is used to find out if all conditions are true here. 
	 */

	for (i = 0; 
		(i < lim - 1) + ((c = getchar()) != EOF) + (c != '\n') == 3; 
		i++)

		s[i] = c;

	if (c == '\n') {

		s[i] = c;
		i++;

	}
	s[i] = '\0';

	return i;
}

void copy (char to[], char from[])

{
	int	i;

	i = 0;
	while ((to[i] = from[i]) != '\0')

		i++;
}
