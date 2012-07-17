#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE	101
#define MAXTOKEN	100
#define MAXMACRO	200

enum { 

	UNFINISHED_CONSTANT, 
	TOKEN_TOO_LONG, 
	INVALID_MACRO_NAME, 
	MACRO_TOO_LONG 

};

struct nlist {

	struct nlist	*next;
	char		*name;
	char		*defn;

};

struct nlist	*hashtab[HASHSIZE];

struct nlist 	*lookup (char *s);
struct nlist 	*install (char *name, char *defn);
int 		read_directive (char *token);
int 		gettoken (char *token, int lim);

int main ()

{
	int		newline, t;
	char		token[MAXTOKEN];
	struct nlist	*np;
	
	newline = !0;
	t = gettoken(token, MAXTOKEN);
	for ( ; ; ) {
	
		if (t == EOF)

			break;

		else if (t == UNFINISHED_CONSTANT) {

			printf("\nUnfinished character or string constant!\n");
			return 1;

		} else if (t == TOKEN_TOO_LONG) {

			printf("\nToken too long!\n");
			return 1;

		} else if (t == INVALID_MACRO_NAME) {
	
			printf("\nInvalid macro name!\n");
			return 1;

		} else if (t == MACRO_TOO_LONG) {

			printf("\nMacro is too long!\n");
			return 1;

		} else if (newline && t == '#') {

			t = read_directive(token);
			continue;

		} else if (isalpha(t) || t == '_' || isdigit(t))

			/* Do macro replacement if needed. */

			if ((isalpha(t) || t == '_') 
			&& (np = lookup(token)) != NULL)

				printf("%s ", np->defn);

			else 
			
				printf("%s ", token);

		else

			printf("%s", token);

		/* Are we at the beginning of a new line? */

		newline = t == '\n';

		t = gettoken(token, MAXTOKEN);

	}

	return 0;
}

unsigned hash (char *s)

{
	unsigned	hashval;

	for (hashval = 0; *s != '\0'; s++)

		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

struct nlist *lookup (char *s)

{	
	struct nlist	*np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)

		if (!strcmp(s, np->name))

			return np;

	return NULL;
}

char	*strdup (char *s);

struct nlist *install (char *name, char *defn)

{
	struct nlist	*np;
	unsigned	hashval;

	if ((np = lookup(name)) == NULL) {

		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)

			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;

	} else

		free((void *) np->defn);

	if ((np->defn = strdup(defn)) == NULL)

		return NULL;

	else

		return np;
}

char *strdup (char *s)

{
        char    *p;

        if ((p = (char *) malloc(strlen(s) + 1)) != NULL)

                strcpy(p, s);

        return p;
}

int	getch (void);
void 	ungetch (int c);
	
/* Only "define" without arguments is supported.  All other preprocessor 
 * directives are ignored (the line is just written as is to the output).  Line 
 * continuations are not supported.  One token of lookahead is always read
 * and returned.  If the macro name is not valid, INVALID_MACRO_NAME is
 * returned.  If the macro replacement is too long, MACRO_TOO_LONG is returned.
 */

int read_directive (char *token)

{
	int	c;
	char	macro[MAXMACRO], *s;
	
	if (isalpha(gettoken(token, MAXTOKEN)) && !strcmp(token, "define")) {

        	if (!isalpha(gettoken(token, MAXTOKEN)))

			return INVALID_MACRO_NAME;

		else {

			s = macro;
                        while ((c = getch()) != '\n' && c != EOF)

				if (s == &macro[MAXMACRO - 1])

					return MACRO_TOO_LONG;

				else

					*s++ = c;

			*s = '\0';
		
			install(token, macro);

		}

	} else {

		/* The entire line is actually ignored. */

       		printf("#%s", token);
                while ((c = getch()) != EOF) {

                	putchar(c);
			if (c == '\n')

				break;

		}

	}
        if (c != EOF)

        	ungetch(c);

	return gettoken(token, MAXTOKEN);
}

/* Read a token and return its first character.  Return an error code if
 * something is wrong, or EOF if the end of file is reached.
 */

int gettoken (char *token, int lim)

{
	int	c, d;
	char	*t = token;

	/* Skip spaces, except newline characters, and comments. */

	for ( ; ; ) {

		while (isspace(c = getch()))

			if (c == '\n') 

				break;

		if (c == EOF)

			return EOF;

		else if (c == '/') {

			if ((d = getch()) != '*') {

				ungetch(d);
				break;

			} else 

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

		} else

			break;

	}

	*t++ = c;
	if (c == '\'') {

		/* Read a character constant. */

		if ((*t++ = c = getch()) == '\\')

			*t++ = c = getch();

		if ((*t++ = c = getch()) != '\'')

			return UNFINISHED_CONSTANT;

	} else if (c == '\"') {

		/* Read a string constant. */

		for ( ; ; )

			if (--lim <= 1)

				return TOKEN_TOO_LONG;

			else if ((*t++ = c = getch()) == '\"')

				break;

			else if (c == '\\') {

				*t++ = c = getch();
				lim--;

			} else if (c == EOF)

				return UNFINISHED_CONSTANT;

	} else if (isdigit(c)) {

		/* Read a number.  Floating-point numbers are not supported,
		 * but simple digits.decimals numbers will be handled correctly
		 * by the program.
		 */ 

		for ( ; ; )

			if (--lim == 1)

				return TOKEN_TOO_LONG;

			else if (isdigit(*t = getch()))

				t++;

			else {
			
				ungetch(*t);
				break;

			}

	} else if (isalpha(c) || c == '_') {

		/* Read variable name or a keyword. */

		for ( ; ; )

			if (--lim == 1)

				return TOKEN_TOO_LONG;

			else if (isalnum(*t = getch()) || *t == '_')

				t++;

			else {

				ungetch(*t);
				break;

			}

	} 

	/* All special characters are passed as one character tokens. */

	*t = '\0';

	return token[0];
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
