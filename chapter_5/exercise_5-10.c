#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code from exercise 4-6 is modified to take its input from command line.
 * After the last argument, getop() returns a newline which make the expression 
 * evaluator pop the top of the stack and print it.  Next call to getop() 
 * returns EOF which ends the program.
 *
 * Reminder: When entering the expression to evaluate, do not forget to add 
 * '\' escape characters where needed.  Remember that characters such as '*' or
 * '<' will be interpreted by the command shell!
 */ 

#define MAXOP	100
#define NUMBER	'0'

enum {

	COS, 
	SIN, 
	EXP,
	POW,
	SQRT,
	UNKNOWN

};

int     number_arguments;
char    **arguments;
double 	variables[26];

void	clear_stack (void);
void 	push (double f);
double	pop (void);
int 	getop (char s[]);

int main (int argc, char *argv[])

{
	int	i, type;
	double	op1, op2;
	char	s[MAXOP];

	/* If no argument, then do nothing. */

	if ((number_arguments = argc) == 1)

		return 0;

        arguments = argv;

	for (i = 0; i < 26; i++)

		variables[i] = 0.0;

	while ((type = getop(s)) != EOF)

		switch (type) {

			case NUMBER:

				push(atof(s));
				break;

			case '<':
			case '>':

				if ((i = s[0] - 'a') < 0 || i > 26)

					printf("Error: Incorrect variable!\n");

				else {

					if (type == '>')
						
						variables[i] = pop();

					push(variables[i]);

				}
				break;

			case COS:

				push(cos(pop()));
				break;

			case SIN:

				push(sin(pop()));
				break;

			case EXP:

				push(exp(pop()));
				break;

			case POW:

				op2 = pop();
				push(pow(pop(), op2));
				break;

			case SQRT:

				push(sqrt(pop()));			
				break;

			case '!':

				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
				break;

			case '&':

				clear_stack();
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

                        case '=':
                        case '\n':

                                printf("\t%.8g\n", op1 = pop());
                                if (type == '=')

                                        push(op1);

                                break;

			case UNKNOWN:
			default:

				printf("Error: Unknow command %s!\n", s);
				break;

		}

	return 0;
}

#define MAXVAL	100

int	sp = 0;
double	val[MAXVAL];

void clear_stack (void)

{
	sp = 0;
}

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

int getop (char s[])

{
	int	i, c, d;

	if (!number_arguments)

		return EOF;

	else if (--number_arguments == 0)

                return '\n';

	else

	        arguments++;

	while ((s[0] = c = *(*arguments)++) == ' ' || c == '\t')

                ;

	if (c == '<' || c == '>') {
	
		s[0] = *(*arguments)++;	
		return c;

	} else if (isalpha(c)) {

		i = 0;
		while (isalpha(s[++i] = c = *(*arguments)++))

			;

		s[i] = '\0';

		if (!strcmp(s, "cos"))

			return COS;

		else if (!strcmp(s, "sin"))

			return SIN;

		else if (!strcmp(s, "exp"))
	
			return EXP;

		else if (!strcmp(s, "pow"))

			return POW;

		else if (!strcmp(s, "sqrt"))

			return SQRT;

		else

			return UNKNOWN;
	
	} else if (!isdigit(c) && c != '.') {

		if (c == '-') {

			if (isdigit(d = *(*arguments)++) || d == '.')

				s[i = 1] = c = d;

			else {

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

                while (isdigit(s[++i] = c = *(*arguments)++))

                        ;

        if (c == '.')

                while (isdigit(s[++i] = c = *(*arguments)++))

                        ;

	s[i] = '\0';

	return NUMBER;
}
