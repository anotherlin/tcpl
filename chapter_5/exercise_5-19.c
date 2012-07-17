#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN	100
#define MAXOUTPUT	1000

enum { NAME, PARENS, BRACKETS };

int	gettoken (void);

int	tokentype;
char	token[MAXTOKEN];
char	out[MAXOUTPUT];

int main ()

{
	char	temp[MAXOUTPUT];

	while (gettoken() != EOF) {

		strcpy(out, token);
		gettoken();
		while (tokentype != '\n') {

                        if (tokentype == PARENS || tokentype == BRACKETS)

				strcat(out, token);

			else if (tokentype == '*') {

				int	count = 0;

				do {

					count++;
					gettoken();

				} while (tokentype == '*');

				temp[0] = '\0';
				if (tokentype != NAME) 

					strcat(temp, "(");

				while (count--)

					strcat(temp, "*");

				strcat(temp, out);

				if (tokentype != NAME) 

					strcat(temp, ")");
				
				strcpy(out, temp);

				continue;

			} else if (tokentype == NAME) {

				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);

			} else

				printf("Error: Invalid input at %s!\n", token);

			gettoken();

		}
		printf("%s\n", out);

	}

	return 0;
}

int     getch (void);
void    ungetch (int c);

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

		for (*p++ = c; (*p++ = getch()) != ']'; )

			;

		*p = '\0';

		return tokentype = BRACKETS;

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
