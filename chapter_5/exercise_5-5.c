#include <stdio.h>

void strncpy (char *s, char *t, int n)

{
	do	

		/* Note that if n is too small, there will be no '\0' at the 
		 * end of the copied string, which is always n characters longs
		 * at most.
		 */
	
		if (n-- == 0) 

			return;

	while ((*s++ = *t++));

	/* If n is bigger than the source string, pad the end of the 
	 * destination string with zeros.
	 */

	while (n--)

		*s++ = '\0';
}

void strncat (char *s, char *t, int n)

{
	while (*s)

		s++;

	do 

		if (n-- == 0) {

			/* Concatenated string is always null terminated, so it
			 * is at most n + 1 characters long.
			 */

			*s = '\0';
			return;

		}

	while ((*s++ = *t++));
}

int strncmp (char *s, char *t, int n)

{
	while (n--)

		if (*s != *t)

			return *s - *t;

		else if (*s == '\0')

			return 0;

		else {

			s++;
			t++;

		}

	return 0;
}

int main ()

{
	char	s[] = "prefix123", t[100] = "", u[] = "456";

	printf("strncpy(\"%s\", \"%s\", 10)", t, s);
	strncpy(t, s, 10);
	printf(" = \"%s\"\n", t);

	printf("strncat(\"%s\", \"%s\", 3)", t, u);
	strncat(t, u, 3);
	printf(" = \"%s\"\n", t);

	printf("strncmp(\"%s\", \"%s\", 9) = %d\n", s, t, strncmp(s, t, 9));

	return 0;
}
