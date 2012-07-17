#include <stdio.h>

void strcat (char *s, char *t)

{
	while (*s)

		s++;

	while ((*s++ = *t++))

		;
}

int main ()

{
	/* Size of array s is specified, that way some extra characters are 
	 * reserved for the upcoming concatenation.
	 */
	
	char	s[100] = "concatenated ", t[] = "string";

	printf("strcat(\"%s\", \"%s\")", s, t);
	strcat(s, t);
	printf(" = \"%s\"\n", s);

	return 0; 
}
