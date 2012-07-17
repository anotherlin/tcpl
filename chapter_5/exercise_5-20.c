#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKEN	100
#define MAXOUTPUT	1000

/* "const" and "register" qualifiers (the word "qualifier" is used informally 
 * as "register" is actually a storage class specifier) are supported, as well 
 * as "char", "int", and "double" types.
 */

enum { QUALIFIER, TYPE, NAME, NUMBER };

int	fulldcl (int is_param, 
		char *qualifier, char *type, char *name,
		char *out);
int	dcl (char *qualifier, char *type, char *name, char *out);
int	dirdcl (char *qualifier, char *type, char *name, char *out);
int	param (char *out);

int	gettoken (void);

int	tokentype;
char	token[MAXTOKEN];

int main () 

{
	while (gettoken() != EOF) {

		char	qualifier[MAXTOKEN], type[MAXTOKEN], name[MAXTOKEN],
			out[MAXOUTPUT];

		/* If input is erroneous, ignore line. */		

		if (fulldcl(0, qualifier, type, name, out)) 

			while (gettoken() != '\n' && tokentype != EOF)

				;

	}
	return 0;
}

int fulldcl (int is_param, char *qualifier, char *type, char *name, char *out)

{
	if (tokentype == QUALIFIER) {

		strcpy(qualifier, token);
		gettoken();

	} else

		qualifier[0] = '\0';
	
	if (tokentype != TYPE) {

		printf("Error: No data type!\n");
		return !0;

	} else {

		strcpy(type, token);
		out[0] = '\0';
		if (dcl(qualifier, type, name, out))

			return !0;

	}

	if (!is_param) {

		if (tokentype != '\n') {

			printf("Error: Syntax error!\n");
			return !0;
	
		}

		printf("%s: %s ", name, out);
		if (qualifier[0] != '\0')

			printf("%s ", qualifier);

		printf("%s\n", type);

	}

	return 0;
}

int dcl (char *qualifier, char *type, char *name, char *out)

{
	int	ns;

	for (ns = 0; gettoken() == '*'; )

		ns++;

	if (dirdcl(qualifier, type, name, out))

		return !0;

	else {

		while (ns-- > 0)

			strcat(out, " pointer to");

		return 0;

	}
}

int dirdcl (char *qualifier, char *type, char *name, char *out)

{
	if (tokentype == '(') {

		if (dcl(qualifier, type, name, out))

			return !0;

		else if (tokentype != ')') {

			printf("Error: Missing ')'!\n");
			return !0;

		}

	} else if (tokentype == NAME) 

		strcpy(name, token);

	else {

		printf("Error: Expected name or (dcl)!\n");
		return !0;

	}

	while (gettoken() == '(' || tokentype == '[')

		if (tokentype == '(') {

			strcat(out, " function ");
			if (gettoken() != ')' && param(out))

				return !0;

			else if (tokentype != ')') {

				printf("Error: Missing ')'!\n");
				return !0;

			} else

				strcat(out, " returning");

		} else {

			/* Array size if any, must be a number or a name. */

			strcat(out, " array[");
			if (gettoken() == NUMBER || tokentype == NAME) {

				strcat(out, token);
				gettoken();

			}

			if (tokentype != ']') {

				printf("Error: Missing ']'!\n");
				return !0;

			} else

				strcat(out, "] of");

		}

	return 0;
}

/* All function parameters must be named. */

int param (char *out)

{
	char	q[MAXTOKEN], t[MAXTOKEN], n[MAXTOKEN], o[MAXOUTPUT];

	strcat(out, "(");
	for ( ; ; ) {

		if (fulldcl(!0, q, t, n, o))

			return !0;

		else {

			strcat(out, n);
			strcat(out, ": ");
			strcat(out, o);
			strcat(out, " ");
			if (q[0] != '\0') {

				strcat(out, q);
				strcat(out, " ");

			}
			strcat(out, t);

		}

		if (tokentype == ')')

			break;

		else if (tokentype != ',') {

			printf("Error: Expecting a ','!\n");
			return !0;

		}

	}
	strcat(out, ")");

	return 0;
}

int	getch (void);
void	ungetch (int c);

int gettoken (void)

{
	int	c;
	char	*p = token;

	while ((c = getch()) == ' ' || c == '\t')

		;

	if (isalpha(c)) {

		for (*p++ = c; isalnum(c = getch()); *p++ = c)

			;
	
		*p = '\0';
		ungetch(c);

		if (!strcmp(token, "const") || !strcmp(token, "register"))

			return tokentype = QUALIFIER;

		else if (!strcmp(token, "char") 
		|| !strcmp(token, "int")
		|| !strcmp(token, "double"))

			return tokentype = TYPE;

		else

			return tokentype = NAME;

	} else if (isdigit(c)) {

		for (*p++ = c; isalpha(c = getch()); *p++ = c)

			;
		
		*p = '\0';
		ungetch(c);

		return tokentype = NUMBER;

	} else

		return tokentype = c;
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
