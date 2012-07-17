#include <stdio.h>
#include <string.h>

/* MAXCHARS bytes are allocated for lines.  As readlines() do not have to call
 * alloc() anymore, but just have to increment a pointer instead, it is faster.
 */

#define MAXLINES	5000
#define MAXCHARS	100000

char	*lineptr[MAXLINES];
char	linebuf[MAXCHARS];

int	readlines (char *lineptr[], int maxlines, char linebuf[]);
void	writelines (char *lineptr[], int nlines);

void	qsort (char *v[], int left, int right);

int main ()

{
	int	nlines;

	if ((nlines = readlines(lineptr, MAXLINES, linebuf)) >= 0) {

		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;

	} else {

		printf("Error: Input too big to sort!\n");
		return 1;

	}
}

#define MAXLEN	1000

int 	getline (char line[], int limit);

int readlines (char *lineptr[], int maxlines, char linebuf[])

{
	int	len, nlines;
	char	*p, line[MAXLEN];

	nlines = 0;
	p = linebuf;
	while ((len = getline(line, MAXLEN)) > 0) 

		if (nlines >= maxlines || p + len > linebuf + MAXCHARS)

			return -1;

		else {

			/* Delete newline, correct if no line reaches MAXLEN
			 * length, otherwise last character is lost. 
 			 */

			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;

		}

	return nlines;
}

void writelines (char *lineptr[], int nlines)

{
	int	i;

	for (i = 0; i < nlines; i++)

		printf("%s\n", lineptr[i]);
}

int getline (char line[], int limit)

{
        int     i, c;

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

void	swap (char *v[], int i, int j);
	
void qsort (char *v[], int left, int right)

{
	int	i, last;

	if (left >= right)

		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)

		if (strcmp(v[i], v[left]) < 0)

			swap(v, ++last, i);

	swap(v, left, last);

	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap (char *v[], int i, int j)

{
	char	*temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
