#include <ctype.h>
#include <stdio.h>

#define TABSIZE		8
#define LINESIZE	80

/* Header and footer are 2 lines long each, so each page is a total of 
 * PAGESIZE + 4 lines.
 */

#define PAGESIZE	40

char	*filename;
int	page, line;

void printheader (void)

{
	printf("%.*s\n\n", LINESIZE, filename);
	page++;
	line = 0;
}

void printfooter (void)

{
	while (line++ % PAGESIZE) 

		putchar('\n');

	printf("\nPage %d\n", page);
}

void printfile (FILE *fp)

{
	int	column, c;

	column = 0;
	while ((c = fgetc(fp)) != EOF) {

		if (c == '\t')

			column += TABSIZE;

		else if (c == '\n') {

			putchar('\n');
			if (++line % PAGESIZE == 0) {

				printfooter();
				printheader();

			}
			column = 0;

			continue;

		} else

			column++;

		if (isprint(c) || c == '\t') {

			if (column > LINESIZE) {

				putchar('\n');
				if (++line % PAGESIZE == 0) {

					printfooter();
					printheader();

				}
				column = c == '\t' ? TABSIZE : 1;

			}
			putchar(c);

		} else {

			if ((column += 3) > LINESIZE) {

				putchar('\n');
				if (++line % PAGESIZE == 0) {

					printfooter();
					printheader();

				}
				column = 4;

			}
			printf("\\x%.2x", c);

		}

	}	
}

int main (int argc, char *argv[])

{
	if (argc == 1)

		printf("Usage: print files\n");

	else

		while (--argc) {

			FILE	*fp;

			if ((fp = fopen(*++argv, "rb")) == NULL) {

				fprintf(stderr, 
					"Error: Cannot open %s!\n", 
					*argv);
				return -1;

			}

			filename = *argv;
			page = 0;

			printheader();
			printfile(fp);
			printfooter();

			fclose(fp);

		}

	return 0;
}
