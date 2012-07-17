#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE	1000
	
int 	getline (FILE *fp, char *line, int max);

int main (int argc, char *argv[])

{
	int	c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')

		while ((c = *++argv[0]) != '\0')

			switch (c) {

				case 'x':

					except = 1;
					break;

				case 'n':

					number = 1;
					break;

				default:

					fprintf(stderr, 
						"Error: Illegal option %c!\n", 
						c);
					return -1;

			}

	if (!argc) 

		printf("Usage: find -x -n pattern [files]\n");

	else {

		char	*p, line[MAXLINE];
		FILE	*fp;

		p = *argv++;
		if (--argc)

			fp = fopen(*argv, "rb");

		else

			fp = stdin;

		for ( ; ; ) {

			int	lineno = 0;

			if (fp == NULL) {

				fprintf(stderr, 
					"Error: Cannot open %s!\n",
					*argv);
				return -1;

			}

			while (getline(fp, line, MAXLINE) > 0) {

				lineno++;
				if ((strstr(line, p) != NULL) != except) {

					/* Except for stdin, when a matching
					 * line is found, name of the file is
					 * printed.
					 */

					if (fp != stdin)

						printf("%s: ", *argv);

					if (number)

						printf("%d: ", lineno);

					printf("%s", line);
					found++;

				}

			}

			if (--argc)

				fp = fopen(*++argv, "rb");

			else

				break;

		}

	}

	return found;
}

int getline (FILE *fp, char *line, int max)

{
	if (fgets(line, max, fp) == NULL)

		return 0;

	else

		return strlen(line);
}
