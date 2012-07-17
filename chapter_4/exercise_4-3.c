#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Further exercises about the reverse polish calculator will build upon each
 * other.
 */

#define MAXOP	100
#define NUMBER	'0'

void 	push (double f);
double	pop (void);
int 	getop (char s[]);

int main ()

{
	int	type;
	double	op1, op2;
	char	s[MAXOP];

	while ((type = getop(s)) != EOF)

		switch (type) {

			case NUMBER: 

				push(atof(s));
				break;
		
			case '+': 
			case '*': 

				if (type == '+')

					push(pop() + pop());
			
				else

					push(pop() * pop());

				break;

			case '-': 

				op2 = pop();
				push(pop() - op2);
				break;

			case '/':
			case '%':

				/* The '%' modulus operator has the same 
				 * behavior as fmod() of math.h.
				 */

				if ((op2 = pop()) != 0.0) {

					if (type == '/')

						push(pop() / op2);

					else {

						op1 = pop();
						push(op1 
							- op2 
							* ((int) (op1 / op2)));

					}

				} else

					printf("Error: Zero divisor!\n");

				break;

			case '\n':

				printf("\t%.8g\n", pop());
				break;

			default:

				printf("Error: Unknow command %s!\n", s);
				break;

		}

	return 0;
}

#define MAXVAL	100

int	sp = 0;
double	val[MAXVAL];

void push (double f)

{
	if (sp < MAXVAL)

		val[sp++] = f;

	else

		printf("Error: Stack is full, cannot push %g!\n", f);
}

double pop (void)

{
	if (sp > 0)

		return val[--sp];

	else {

		printf("Error: Stack is empty, cannot pop!\n");
		return 0.0;

	}
}

int	getch (void);
void	ungetch (int c);

int getop (char s[])

{
	int	i, c, d;

	while ((s[0] = c = getch()) == ' ' || c == '\t')

		;

	if (!isdigit(c) && c != '.') {

		if (c == '-') {

			if (isdigit(d = getch()) || d == '.')

				s[i = 1] = c = d;

			else {

				if (d != EOF)

					ungetch(d);

				s[1] = '\0';
				return c;

			}

		} else {

			s[1] = '\0';
			return c;

		}

	} else
		
		i = 0;

	if (isdigit(c)) 

		while (isdigit(s[++i] = c = getch()))

			;

	if (c == '.')

		while (isdigit(s[++i] = c = getch()))

			;

	s[i] = '\0';
	if (c != EOF)

		ungetch(c);

	return NUMBER;
}

#define BUFSIZE	100

char	buf[BUFSIZE];
int	bufp = 0;

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
