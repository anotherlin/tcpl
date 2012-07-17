#include <stdio.h>
#include <string.h>

void reverse (char s[])

{
	int	t, l;

	if (strlen(s) < 2)

		return;

	else {

		t = s[0];
		s[0] = s[l = strlen(s) - 1];
		s[l] = '\0';
		reverse(s + 1);
		s[l] = t;

	}
}

#define BUFFER_SIZE		16
#define NUMBER_TEST_STRINGS	4

char *TEST_STRINGS[NUMBER_TEST_STRINGS] = {

	"x",
	"ab",
	"abc",
	"reverse"

};

int main ()

{
	int	i, j;
	char	s[BUFFER_SIZE];

	for (i = 0; i < NUMBER_TEST_STRINGS; i++) {

		/* As some compilers, for example gcc, consider literal strings
		 * as constants and put them in a read-only section of the 
		 * memory, it is safer to copy the test strings into a 
		 * temporary buffer where they can then be reversed. 
		 */

		j = 0;
		while ((s[j] = TEST_STRINGS[i][j]) != '\0')

			j++;

		printf("reverse(\"%s\") = ", s);
		reverse(s);
		printf("\"%s\"\n", s);

	}

	return 0;
}
