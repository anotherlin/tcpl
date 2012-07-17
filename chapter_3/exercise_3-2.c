#include <stdio.h>

void escape (char s[], char t[])

{
	int	i, j;

	for (i = j = 0; s[i] != '\0'; i++, j++)

		switch (s[i]) {

			case '\n':	

				t[j++] = '\\'; 
				t[j] = 'n'; 
				break;

			case '\t':	

				t[j++] = '\\'; 
				t[j] = 't'; 
				break;

			default:	

				t[j] = s[i]; 
				break;

		}

	t[j] = '\0';
}

void unescape (char s[], char t[])

{
	int	i, j;

	for (i = j = 0; s[i] != '\0'; i++, j++)

		if (s[i] == '\\')

			switch (s[++i]) {

				case 't':	

					t[j] = '\t'; 
					break;

				case 'n':	

					t[j] = '\n'; 
					break;

				default: 

					t[j++] = '\\'; 
					t[j] = s[i];
					break;

			}

		else

			t[j] = s[i];

	t[j] = '\0';
}

#define BUFFER_SIZE	100

int main ()

{
	char	p[BUFFER_SIZE], q[BUFFER_SIZE];
	
	escape("A newline\nthen a tab\t", p);
	printf("escaped: \"%s\".\n", p);

	unescape(p, q);
	printf("un-escaped: \"%s\".\n", q);

	return 0;
}
