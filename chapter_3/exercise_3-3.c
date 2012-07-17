#include <ctype.h>
#include <stdio.h>

void expand (char s1[], char s2[])

{
	int	i, j, k;

	for (i = j = 0; s1[i] != '\0'; )

		if (isalnum(s1[i]) && s1[i + 1] == '-' && isalnum(s1[i + 2])) {

			if ((isupper(s1[i]) && isupper(s1[i + 2])
				|| islower(s1[i]) && islower(s1[i + 2])
				|| isdigit(s1[i]) && isdigit(s1[i + 2]))
			&& s1[i] < s1[i + 2]) {

				for (k = s1[i]; k < s1[i + 2]; k++)
			
					s2[j++] = k;
	
				i += 2;

			} else {

				s2[j++] = s1[i++];
				s2[j++] = s1[i++];

			}

		} else

			s2[j++] = s1[i++];

	s2[j] = '\0';
}

#define BUFFER_SIZE		100
#define NUMBER_TEST_STRINGS	5

char *TEST_STRINGS[NUMBER_TEST_STRINGS] = {

	"a-b-c",
	"a-z0-9",
	"-a-z",
	"A-Z-",
	"0-aZ-A-uv-z-c"

};

int main ()

{
	int	i;
	char	s[BUFFER_SIZE];
	
	for (i = 0; i < NUMBER_TEST_STRINGS; i++) {

		expand(TEST_STRINGS[i], s);
		printf("\"%s\" => \"%s\"\n", TEST_STRINGS[i], s);

	}

	return 0;
}
