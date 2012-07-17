#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE	101

struct nlist {

	struct nlist	*next;
	char		*name;
	char		*defn;

};

struct nlist	*hashtab[HASHSIZE];

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

void undef (char *name)

{
	struct nlist	*pp, *np;

	for (pp = NULL, np = hashtab[hash(name)]; 
		np != NULL; 
		pp = np, np = np->next)

		if (!strcmp(name, np->name)) {

			if (pp == NULL)

				hashtab[hash(name)] = np->next;

			else

				pp->next = np->next;

			free(np->name);
			free(np->defn);
			free(np);

			return;

		}
}

#define TESTNAME	"test"

int main ()

{
	printf("Looking up \"%s\": %s.\n", 
		TESTNAME, 
		lookup(TESTNAME) != NULL ? "found" : "not found");

	install(TESTNAME, "");

	printf("Looking up \"%s\": %s.\n", 
		TESTNAME, 
		lookup(TESTNAME) != NULL ? "found" : "not found");

	undef(TESTNAME);

	printf("Looking up \"%s\": %s.\n", 
		TESTNAME, 
		lookup(TESTNAME) != NULL ? "found" : "not found");

	return 0;
}
