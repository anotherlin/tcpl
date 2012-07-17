#include <stdio.h>

#define NOTHING         0
#define COMMENT         1
#define DOUBLE_QUOTE    2
#define SINGLE_QUOTE    3
                        
int main ()

{
        int     state, c, d;

        state = NOTHING;
	while ((c = getchar()) != EOF)

                if (state == NOTHING) {

                        if (c == '/') {

				do {

                        		if ((d = getchar()) == '*')

                                                state = COMMENT;

                                        else

                                                putchar(c);

 					c = d;

				} while (c == '/');

				if (state != COMMENT && c != EOF)
				
					putchar(c);

                        } else {

                                if (c == '\"')

                                        state = DOUBLE_QUOTE;

                                else if (c == '\'')

                                        state = SINGLE_QUOTE;

                                putchar(c);

                        }

                } else if (state == COMMENT) {

                        while (c == '*')

                                if ((c = getchar()) == '/')

                                        state = NOTHING;

                } else {

                        if (c == '\\') {

                                putchar(c);
                                c = getchar();

                        } else if (state == DOUBLE_QUOTE && c == '\"'
                        || state == SINGLE_QUOTE && c == '\'')

                                state = NOTHING;

                        if (c != EOF)

                                putchar(c);

                }

        return 0;
}
