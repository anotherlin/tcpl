#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD	100

/* References are stored in doubly-linked lists, last lines of occurence first.
 * Both insertion and printing are hence fast.
 */

struct rnode {

	int		line;
	struct rnode 	*previous;
	struct rnode	*next;

};

struct tnode {

	int		is_noise;
	char		*word;

	struct rnode	*refs;	/* NULL if is_noise is not zero. */

	struct tnode	*left;
	struct tnode	*right;

};

char *NOISE_WORDS[] = {

	"the",
	"and",
	"of",

	/* And so on... */

};

int	line = 1;

struct tnode	*addtree (struct tnode *p, char *w, int is_noise);
void		treeprint (struct tnode *p);
int 		getword (char *word, int lim);

int main ()

{
	struct tnode	*root;
	int		i;
	char		word[MAXWORD];

	root = NULL;

	/* Insert the noise words in the binary tree. */ 

	for (i = 0; i < sizeof NOISE_WORDS / sizeof NOISE_WORDS[0]; i++)

		root = addtree(root, NOISE_WORDS[i], !0);

	/* Read words and collect line numbers. */

	while (getword(word, MAXWORD) != EOF)

		if (isalpha(word[0]))

			root = addtree(root, word, 0);

	/* Print the "index" just built. */	

	treeprint(root);

	return 0;
}

struct tnode	*talloc (void);
struct rnode	*ralloc (void);
char		*strdup (char *s);

struct tnode *addtree (struct tnode *p, char *w, int is_noise)

{
	int	cond;

	if (p == NULL) {

		p = talloc();
		p->is_noise = is_noise;
		p->word = strdup(w);
		if (!is_noise) {

			p->refs = ralloc();

			p->refs->line = line;
			p->refs->previous = p->refs->next = p->refs;

		} else

			p->refs = NULL;

		p->left = p->right = NULL;

	} else if ((cond = strcmp(w, p->word)) == 0) {

		if (!p->is_noise && p->refs->line != line) {

			struct rnode	*r;

			r = ralloc();

			r->line = line;

			r->previous = p->refs->previous;
			r->next = p->refs;

			r->previous->next = r;
			r->next->previous = r;

			p->refs = r;

		}
	
	} else if (cond < 0)

		p->left = addtree(p->left, w, is_noise);

	else

		p->right = addtree(p->right, w, is_noise);

	return p;
}

struct tnode *talloc (void)

{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct rnode *ralloc (void)

{
	return (struct rnode *) malloc(sizeof(struct rnode));
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
		if (!p->is_noise) {

			struct rnode 	*r;

			printf("%s:\t", p->word);

			/* Lines of occurence are printed sorted. */

			r = p->refs->previous;
			for ( ; ; ) {

				printf("%d, ", r->line); 
				if (r == p->refs)

					break;

				else
	
					r = r->previous;

			} 
			putchar('\n');

		}
		treeprint(p->right);

	}
}

int 	getch (void);
void	ungetch (int c);

int getword (char *word, int lim)

{
	int	c;
	char	*w = word;

	while (isspace(c = getch()))
	
		if (c == '\n')

			line++;

	if (c != EOF)

		*w++ = c;

	if (!isalpha(c)) {

		*w = '\0';
		return c;

	}

	for ( ; --lim > 1; w++)

		if (!isalnum(*w = getch())) {
	
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
