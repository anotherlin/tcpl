#include <stdio.h>

#define NOTHING         0
#define COMMENT         1
#define DOUBLE_QUOTE    2
#define SINGLE_QUOTE    3

int	line;

void 	print_error (char s[]);
                        
int main ()

{
        int     state, 
		parentheses, brackets, braces, 
		c;

	line = 1;

        state = NOTHING;
	parentheses = brackets = braces = 0;
	while ((c = getchar()) != EOF)

                if (state == NOTHING) {

                        if (c == '/') {

				do

                        		if ((c = getchar()) == '*')

                                                state = COMMENT;

				while (c == '/');

                        } else {

                                if (c == '\"')

                                        state = DOUBLE_QUOTE;

                                else if (c == '\'')

                                        state = SINGLE_QUOTE;

				else if (c == '\n')

					line++;

				else if (c == '(') 
	
					parentheses++;

				else if (c == ')') {

					if (--parentheses < 0) {

						print_error("Unbalanced "
							"parentheses");
						return -1;

					}

				} else if (c == '[')

					brackets++;

				else if (c == ']') {

					if (--brackets < 0) {

						print_error(
							"Unbalanced brakets");
						return -1;

					}

				} else if (c == '{') 

					braces++;

				else if (c == '}') {

					if (--braces < 0) {

						print_error(
							"Unbalanced braces");
						return -1;

					}

				}

                        }

                } else if (state == COMMENT) {

			if (c == '\n')

				line++;

			else

	                        while (c == '*')

        	                        if ((c = getchar()) == '/')

               					state = NOTHING;

                } else {
		
			if (c == '\n') {

				print_error(
					"Newline character inside a "
					"double or single quote");
				return -1;

			} else if (c == '\\')

				c = getchar();

                        else if (state == DOUBLE_QUOTE && c == '\"'
                        || state == SINGLE_QUOTE && c == '\'')

                                state = NOTHING;

                }

	/* Check that comments and quoted strings or characters are terminated
 	 * before the end of file.
	 */

	if (state == COMMENT) {

		print_error("Unterminated comment");
		return -1;

	} else if (state == DOUBLE_QUOTE || state == SINGLE_QUOTE) {

		print_error("Unterminated double or single quote");
		return -1;

	} else

	        return 0;
}

void print_error (char s[])

{
	printf("Error (%d): %s!\n", line, s); 
} 
