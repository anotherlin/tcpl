#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN	100
#define MAXOUTPUT	1000

enum { NAME, PARENS, BRACKETS, ERROR };

/* dcl() and dirdcl() return non-zero if the input is erroneous. */

int	dcl (void);
int	dirdcl (void);

int	gettoken (void);

int	tokentype;
char	token[MAXTOKEN];
char	name[MAXTOKEN];
char	datatype[MAXTOKEN];
char	out[MAXOUTPUT];

int main () 

{
	while (gettoken() != EOF) {

		int	r;

		/* Check that data type is a "name". */

		if (tokentype != NAME) {

			r = !0;
			printf("Error: No data type!\n");

		} else {

			strcpy(datatype, token);
			out[0] = '\0';
			r = dcl();

		}

		if (r || tokentype != '\n') {

			if (!r && tokentype != '\n')

				printf("Error: Syntax error!\n");

			/* If input is erroneous, ignore line. */		

			while (gettoken() != '\n' && tokentype != EOF)

				;

		} else

			printf("%s: %s %s\n", name, out, datatype);

	}
	return 0;
}

int dcl (void)

{
	int	ns;

	for (ns = 0; gettoken() == '*'; )

		ns++;

	if (dirdcl())

		return !0;

	else {

		while (ns-- > 0)

			strcat(out, " pointer to");

		return 0;

	}
}

int dirdcl (void)

{
	if (tokentype == '(') {

		if (dcl())

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

	while (gettoken() == PARENS || tokentype == BRACKETS)

		if (tokentype == PARENS)

			strcat(out, " function returning");

		else {

			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");

		}

	if (tokentype == ERROR)

		return !0;

	else

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

	if (c == '(') {

		if ((c = getch()) == ')') {

			strcpy(token, "()");
			return tokentype = PARENS;

		} else {

			ungetch(c);
			return tokentype = '(';

		}

	} else if (c == '[') {

		for (*p++ = c; (c = getch()) != EOF && c != ']'; *p++ = c)

			;

		if (c != EOF)

			*p++ = c;

		*p = '\0';
		if (c == ']')

			return tokentype = BRACKETS;

		else

			return ERROR;

	} else if (isalpha(c)) {

		for (*p++ = c; isalnum(c = getch()); )

			*p++ = c;
		
		*p = '\0';
		ungetch(c);

		return tokentype = NAME;

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
