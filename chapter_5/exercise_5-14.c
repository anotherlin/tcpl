#include <ctype.h>
#include <stdio.h>

/* To avoid declaration clashes with functions qsort(), atof(), strcmp(), and 
 * strcpy(), stdlib.h and string.h are not included.  All these functions have
 * been rewritten.  However, they may still conflict with built-in functions,
 * if any. 
 *
 * Further exercises about sorting will build upon each other.
 */

#define MAXLINES	5000

int	numeric = 0;

/* Sorting comparison results are multiplied with reverse, -1 will make qsort()
 * sort in decreasing order.
 */

int	reverse = 1;

char	*lineptr[MAXLINES];

int	readlines (char *lineptr[], int maxlines);
void	writelines (char *lineptr[], int nlines);

void 	qsort (void *v[], 
		int left, int right, 
		int (*comp) (void *, void *));
int	numcmp (char *s1, char *s2);
int	strcmp (char *s, char *t);
		
int main (int argc, char *argv[])

{
	int	c, nlines;

	while (--argc > 0 && (*++argv)[0] == '-')

		while ((c = *++argv[0]))

			switch (c) {

				case 'n':	
					
					numeric = !0; 
					break;

				case 'r': 	
		
					reverse = -1; 
					break;

				default:

					printf("Error: Illegal option '%c'.\n",
						c);
					return 1;

			}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

		qsort((void **) lineptr, 
			0, nlines -1,
			(int (*)(void *, void *)) (numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;

	} else {

		printf("Error: Input too big to sort!\n");
		return 1;

	}
}

#define MAXLEN	1000

int 	getline (char line[], int limit);
char	*alloc (int n);
void	strcpy (char *s, char *t);

int readlines (char *lineptr[], int maxlines)

{
	int	len, nlines;
	char	*p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) 

		if (nlines >= maxlines || (p = alloc(len)) == NULL)

			return -1;

		else {

			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;

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

#define ALLOCSIZE	100000

char 	allocbuf[ALLOCSIZE];
char	*allocp = allocbuf;

char *alloc (int n)

{
	if (allocbuf + ALLOCSIZE - allocp >= n) {

		allocp += n;
		return allocp - n;

	} else

		return NULL;
}

void strcpy (char *s, char *t)

{
	while ((*s++ = *t++))

		;
}

void 	swap (void *v[], int i, int j);

void qsort (void *v[], int left, int right, int (*comp) (void *, void *))

{
	int	i, last;

	if (left >= right)

		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)

		if (reverse * (*comp)(v[i], v[left]) < 0)

			swap(v, ++last, i);

	swap(v, left, last);

	qsort(v, left, last - 1, comp);
	qsort(v, last + 1, right, comp);
}

void swap (void *v[], int i, int j)

{
        void    *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

double 	atof (char s[]);

int numcmp (char *s1, char *s2)

{
	double	v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)

		return -1;

	else if (v1 > v2)

		return 1;

	else

		return 0;
}

int strcmp (char *s, char *t)

{
	for ( ; *s == *t; s++, t++)

		if (*s == '\0')

			return 0;

	return *s - *t;
}

double atof (char s[])

{
        double  val, power;
        int     i, sign;

        for (i = 0; isspace(s[i]); i++)

                ;

        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')

                i++;

        for (val = 0.0; isdigit(s[i]); i++)

                val = 10.0 * val + (s[i] - '0');

        if (s[i] == '.')

                i++;

        for (power = 1.0; isdigit(s[i]); i++) {

                val = 10.0 * val + (s[i] -'0');
                power *= 10.0;

        }

        return sign * val / power;
}
