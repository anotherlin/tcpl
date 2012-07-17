#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP	100
#define NUMBER	'0'

void 	push (double f);
double	pop (void);
int 	getop (double *n);

int main ()

{
	int	type;
	double	n, op2;

	while ((type = getop(&n)) != EOF)

		switch (type) {

			case NUMBER: 

				push(n);
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

				if ((op2 = pop()) != 0.0) 

					push(pop() / op2);

				else 

					printf("Error: Zero divisor!\n");

				break;

			case '\n':

				printf("\t%.8g\n", pop());
				break;

			default:

				printf("Error: Syntax Error!\n");
				return -1;

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

/* Negative numbers are not supported as scanf() is unable to distinguish 
 * "- 2" (substract then push 2) from "-2" (push -2).
 */

int getop (double *n)

{
	int	c;

	while ((c = getchar()) == ' ' || c == '\t')

		;

	if (c == EOF || c == '\n')

		return c;

	else

		switch (c) {

			case '+':
			case '*':
			case '-':
			case '/':

				return c;

			default:

				ungetc(c, stdin);
				if (scanf("%lf", n) == 1) 

					return NUMBER;

				else

					return 0;

		}
}
