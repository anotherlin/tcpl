#include <stdio.h>

int strend (char *s, char *t)

{
	int	n;

	while (*s)

		s++;

	for (n = 0; *t; n++)

		t++;

	while (n--)

		if (*--s != *--t)

			return 0;

	return 1;
}

int main ()

{
	char	s[] = "at the end", t[] = "end", u[] = "and";

	printf("strend(\"%s\", \"%s\") = %d\n", s, t, strend(s, t));
	printf("strend(\"%s\", \"%s\") = %d\n", s, u, strend(s, u));

	return 0;
}
