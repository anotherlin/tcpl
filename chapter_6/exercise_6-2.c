#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PREFIX_LENGTH	6
#define MAXWORD			100

struct tnode {

	char		*word;
	struct tnode	*left;
	struct tnode	*right;

};

char *keytab[] = {

        "auto", 
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while",

};

#define NKEYS   (sizeof keytab / sizeof keytab[0])

int		prefix_length;
char		*last_printed;

int     	binsearch (char *word, char *tab[], int n);
struct tnode	*addtree (struct tnode *p, char *w);
void		treeprint (struct tnode *p);
int 		getword (char *word, int lim);

int main (int argc, char *argv[])

{
	struct tnode	*root;
	char		word[MAXWORD];

	/* Keywords are not inserted in the binary tree. */

	root = NULL;
	while (getword(word, MAXWORD) != EOF)

		if (binsearch(word, keytab, NKEYS) < 0)

			root = addtree(root, word);

	/* Prefix length can be changed using a command line argument. */
	
	prefix_length = argc == 2 ? atoi(argv[1]) : DEFAULT_PREFIX_LENGTH;
	last_printed = NULL;
	treeprint(root);

	return 0;
}

int binsearch (char *word, char *tab[], int n)

{
        int     cond;
        int     low, high, mid;

        low = 0;
        high = n - 1;
        while (low <= high) {

                mid = (low + high) / 2;
                if ((cond = strcmp(word, tab[mid])) < 0)

                        high = mid - 1;

                else if (cond > 0)

                        low = mid + 1;

                else

                        return mid;

        }

        return -1;
}

struct tnode	*talloc (void);
char		*strdup (char *s);

struct tnode *addtree (struct tnode *p, char *w)

{
	int	cond;

	if (p == NULL) {

		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;

	} else if ((cond = strcmp(w, p->word)) < 0)

		p->left = addtree(p->left, w);

	else if (cond > 0)

		p->right = addtree(p->right, w);

	return p;
}

struct tnode *talloc (void)

{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup (char *s)

{
	char	*p;

	if ((p = (char *) malloc(strlen(s) + 1)) != NULL)

		strcpy(p, s);

	return p;
}

void treeprint (struct tnode *p)

{
	if (p != NULL) {

		treeprint(p->left);

		if (last_printed != NULL 
		&& strncmp(p->word, last_printed, prefix_length))

			putchar('\n');

		printf("%s\n", p->word);
		last_printed = p->word;

		treeprint(p->right);

	}
}

int	getch (void);
void	ungetch (int c);

/* See exercise 6-1 for a description of the updated getword() function. */

int getword (char *word, int lim)

{
        int     c, d;
        char    *w = word;

        for ( ; ; ) {

                while (isspace(c = getch()))

                        ;

                if (c == '#') {

                        while ((c = getch()) != '\n')

                                if (c == EOF)

                                        return EOF;

                        continue;

                }

                if (c == '/') {

                        if ((d = getch()) != '*')

                                ungetch(d);

                        else

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

                        continue;

                }

                if (c == '\'') {

                        if ((c = getch()) == '\\')

                                c = getch();

                        if ((c = getch()) != '\'')

                                return EOF;

                        else

                                continue;

                }

                if (c == '\"') {

                        for ( ; ; )

                                if ((c = getch()) == '\"')

                                        break;

                                else if (c == '\\')

                                        c = getch();

                                else if (c == EOF)

                                        return EOF;

                        continue;

                }

                if (!isalpha(c)) {

                        if (c == EOF)

                                return c;

                } else

                        break;

        }

        for (*w++ = c; --lim > 1; w++)

                if (!isalnum(*w = getch()) && *w != '_') {

                        ungetch(*w);
                        break;

                }

        *w = '\0';

        return word[0];
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
