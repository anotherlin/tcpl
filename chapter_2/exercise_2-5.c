#include <stdio.h>

int any (char s1[], char s2[])

{
	int	i, j;

	for (i = 0; s1[i] != '\0'; i++)

		for (j = 0; s2[j] != '\0'; j++)

			if (s1[i] == s2[j])

				return i;

	return -1;
}

int main ()

{
	char	s1[] = "abcdef", 
		s2[] = "xyz",
		s3[] = "opqrsbcd";

	printf("any(\"%s\", \"%s\") = %d\n", s1, s2, any(s1, s2));
	printf("any(\"%s\", \"%s\") = %d\n", s1, s3, any(s1, s3));

	return 0;
}
