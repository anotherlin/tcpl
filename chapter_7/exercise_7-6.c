#include <stdio.h>
#include <string.h>

#define BUFSIZE	80

int main (int argc, char *argv[])

{
	FILE	*f, *g;
	
	if (argc != 3)

		printf("Usage: diff file1 file2\n");

	else if ((f = fopen(argv[1], "rb")) == NULL) {

		fprintf(stderr, "Error: Cannot open %s!\n", argv[1]);
		return -1;

	} else if ((g = fopen(argv[2], "rb")) == NULL) {

		fprintf(stderr, "Error: Cannot open %s!\n", argv[2]);
		return -1;

	} else {

		int	line;
		char	s[BUFSIZE], t[BUFSIZE], *p, *q;

		/* Lines are read in chunks of BUFSIZE characters.  If the 
		 * files differ, the "current" chunks are printed, along with
 		 * the line number.
		 */

		line = 1;
		for ( ; ; ) {

			p = fgets(s, BUFSIZE, f);		
			q = fgets(t, BUFSIZE, g);
			if (p == NULL || q == NULL || strcmp(s, t)) {

				if (p != NULL) {

					if (s[strlen(s) - 1] == '\n')

						s[strlen(s) - 1] = '\0';

					printf("%s: %d: %s\n",
						argv[1], line, s);

				}

				if (q != NULL) {

					if (t[strlen(t) - 1] == '\n')

						t[strlen(t) - 1] = '\0';

					printf("%s: %d: %s\n", 
						argv[2], line, t);

				}
				break;

			} else if (s[strlen(s) - 1] == '\n')

				line++;

		}
		fclose(f);
		fclose(g);

	}	

	return 0;
}
