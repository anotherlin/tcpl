#include <ctype.h>
#include <stdio.h>

/* The fields to sort are supposed to be comma separated, with no space in 
 * between.  The last field of a line doesn't end with a comma.  There is 
 * almost no error checking.
 */

#define MAXFIELDS	10
#define MAXLINES	1000

int	number_fields, current_field;

int	directory[MAXFIELDS];
int	fold[MAXFIELDS]; 
int	numeric[MAXFIELDS];
int	reverse[MAXFIELDS];

char	*fieldsptr[MAXFIELDS][MAXLINES];
int	lines[MAXFIELDS];

int	readlines (void);
void	writelines (int nlines);

void 	qsort (void *v[], 
		int left, int right, 
		int (*comp) (void *, void *));
int	numcmp (char *s1, char *s2);
int	strcmp (char *s, char *t);
		
int main (int argc, char *argv[])

{
	int	i, c, nlines;

	/* By default, all fields are sorted increasingly, in non-folded, non-
	 * directory, and non-numeric modes.
 	 */

	for (i = 0; i < MAXFIELDS; i++)
		
		reverse[i] = 1;

	/* Each option argument changes the sorting order and mode of a field,
	 * left to right.
	 */
	
	number_fields = 0;
	while (--argc > 0 && (*++argv)[0] == '-') {

		while ((c = *++argv[0]))

			switch (c) {

				case 'd': 	

					directory[number_fields] = !0; 
					break;

				case 'f': 	

					fold[number_fields] = !0; 
					break;

				case 'n':	

					numeric[number_fields] = !0; 
					break;

				case 'r': 	

					reverse[number_fields] = -1; 
					break;

				default:

					printf("Error: Illegal option '%c'.\n",
						c);
					return 1;

			}

		if (++number_fields == MAXFIELDS) {

			printf("Error: Too many fields!\n");
			return 1;

		}

	}

	if (!number_fields)

		number_fields = 1;

	if ((nlines = readlines()) >= 0) {

		for (current_field = 0; 
			current_field < number_fields; 
			current_field++)

			qsort((void **) fieldsptr[current_field], 
				0, lines[current_field] - 1,
				(int (*)(void *, void *)) 
					(numeric[current_field] 
						? numcmp 
						: strcmp));

		writelines(nlines);
		return 0;

	} else {

		printf("Error: Input too big to sort!\n");
		return 1;

	}
}

#define MAXLEN	1000

int 	getfield (char field[], int limit);
char	*alloc (int n);
void	strcpy (char *s, char *t);

int readlines (void)

{
	int	nlines, i;
			
	for (nlines = 0; ; nlines++) {

		if (nlines >= MAXLINES) {
			
			printf("Error: Too many lines!\n");
			return -1;

		}

		for (i = 0; i < number_fields; i++) {

			int	length; 
			char	field[MAXLEN], *p;

			if ((length = getfield(field, MAXLEN)) > 0) {

				if ((p = alloc(length)) == NULL) {

					printf("Error: Out of memory!\n");
					return -1;

				} else if (length > 1) {

					int	c;
			
					c = field[length - 1];
					field[length - 1] = '\0';
					strcpy(p, field);
					fieldsptr[i][lines[i]++] = p;

					if (c == '\n') 
						
						break;
			
					else if (c == ','
					&& i == number_fields - 1
					&& ++number_fields == MAXFIELDS) {

						printf("Error: "
							"Too many fields!\n");
						return -1;

					}				

				}

			} else if (i)

				return nlines + 1;
				
			else 

				return nlines;

		}

	}
}

void writelines (int nlines)

{
	int	i, j;

	for (i = 0; i < nlines; i++) {

		for (j = 0; j < number_fields; j++)

			if (i < lines[j])

				printf("%s, ", fieldsptr[j][i]);

			else

				printf(", ");

		putchar('\n');

	}
}

/* getfield() returns the length of the field read.  A zero length means that
 * the end of file has been reached.  A field of one character is empty (this 
 * only character is either ',' or '\n').
 */

int getfield (char field[], int limit)

{
        int     i, c;

        for (i = 0;
		i < limit - 1 
			&& (c = getchar()) != EOF && c != ',' && c != '\n';
                i++)

                field[i] = c;

	if (c == ',' || c == '\n')

		field[i++] = c;	
        
        field[i] = '\0';

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

		if (reverse[current_field] * (*comp)(v[i], v[left]) < 0)

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
        char    a, b;

        for ( ; ; ) {

                if (directory[current_field]) {

                        do

                                a = *s++;

                        while (!isalnum(a) && !isspace(a) && a != '\0');

                        do

                                b = *t++;

                        while (!isalnum(b) && !isspace(b) && b != '\0');

                } else {

                        a = *s++;
                        b = *t++;

                }

                if (fold[current_field]) {

                        a = tolower(a);
                        b = tolower(b);

                }

                if (a != b)

                        break;

                else if (a == '\0')

                        return 0;

        }

        return a - b;
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
