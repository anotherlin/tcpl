#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD	100

/* All keywords, see A2.4, p192 of the book. */

struct key {

	char	*word;
	int	count;

} keytab[] = {

	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0, 
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0, 
	"short", 0,
	"signed", 0,
	"sizeof", 0, 
	"static", 0, 
	"struct", 0,
	"switch", 0,
	"typedef", 0, 
	"union", 0, 
	"unsigned", 0, 
	"void", 0, 
	"volatile", 0, 
	"while", 0,

};

#define	NKEYS	(sizeof keytab / sizeof keytab[0])

int	binsearch (char *word, struct key tab[], int n);
int 	getword (char *word, int lim);

int main ()

{
	int	n;
	char	word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)

		if ((n = binsearch(word, keytab, NKEYS)) >= 0)

			keytab[n].count++;

	for (n = 0; n < NKEYS; n++)

		if (keytab[n].count > 0)

			printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}

int binsearch (char *word, struct key tab[], int n)

{
	int	cond;
	int	low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {

		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)

			high = mid - 1;

		else if (cond > 0)

			low = mid + 1;

		else

			return mid;

	}

	return -1;
}

int 	getch (void);
void	ungetch (int c);

/* getword() now only returns words starting with a letter and followed by 
 * letters, digits, or underscores.  Everything else is skipped and ignored.  
 * It returns EOF if an error is detected or if the end of file is reached. 
 */

int getword (char *word, int lim)

{
	int	c, d;
	char	*w = word;

	for ( ; ; ) {

		/* Skip spaces. */

		while (isspace(c = getch()))

			;

		/* Skip preprocessor directives, line continuations are not
		 * supported. 
		 */

		if (c == '#') {
	
			while ((c = getch()) != '\n')

				if (c == EOF)

					return EOF;

			continue;

		}

		/* Skip comments. */

		if (c == '/') {

			if ((d = getch()) != '*')

				ungetch(d);

			else

				for ( ; ; )

					if ((c = getch()) != '*') {

						if (c == EOF)

							return EOF;

						else
		
							continue;

					} else if ((c = getch()) != '/') {

						if (c == EOF)

							return EOF;

						else {
						
							ungetch(c);
							continue;

						}	

					} else

						break;

			continue;

		}

		/* Skip character and string constants.  Only simple escape 
		 * characters are supported. 
		 */

		if (c == '\'') {

			if ((c = getch()) == '\\')

				c = getch();

			if ((c = getch()) != '\'')

				return EOF;

			else

				continue;

		}

		if (c == '\"') {

			for ( ; ; )

				if ((c = getch()) == '\"')

					break;

				else if (c == '\\')

					c = getch();

				else if (c == EOF)

					return EOF;

			continue;

		}

		/* Ignore all other characters. */

		if (!isalpha(c)) {

			if (c == EOF)

				return c;

		} else

			break;

	}

	/* Read a word. */

	for (*w++ = c; --lim > 1; w++)

		if (!isalnum(*w = getch()) && *w != '_') {
	
			ungetch(*w);
			break;

		}

	*w = '\0';

	return word[0];
}

#define BUFSIZE 100

char    buf[BUFSIZE];
int     bufp = 0;

int getch (void)

{
        return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch (int c)

{
        if (bufp >= BUFSIZE)

                printf("Error: Too many characters!\n");

        else

                buf[bufp++] = c;
}
