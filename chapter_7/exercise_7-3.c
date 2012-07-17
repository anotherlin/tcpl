#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

/* All features mentionned in section 7.2, except computed width and precision,
 * are supported.
 */

void minprintf (char *fmt, ...)

{
	va_list	ap;
	char	conv[100], *p, *q, *sval;
	long	lval;
	int	ival;
	double	dval;
	void	*pval;

	va_start(ap, fmt);
	conv[0] = '%';
	for (p = fmt; *p != '\0'; p++)

		if (*p != '%')

			putchar(*p);

		else {

			p++;
			q = &conv[1];

			if (*p == '-')

				*q++ = *p++;

			while (isdigit(*p))

				*q++ = *p++;

			if (*p == '.')

				*q++ = *p++;

			while (isdigit(*p))

				*q++ = *p++;

			if (*p == 'h' || *p == 'l')

				*q++ = *p++;
			
			*q++ = *p;
			*q = '\0';

			switch (*p) {

				case 'd': case 'i': 
				case 'o':
				case 'x': case 'X':
				case 'u':
				case 'c':

					if (*(q - 2) == 'l') {

						lval = va_arg(ap, long);
						printf(conv, lval);			

					} else {

						ival = va_arg(ap, int);
						printf(conv, ival);

					}
					break;

				case 's':

					sval = va_arg(ap, char *);
					printf(conv, sval);
					break;

				case 'f':
				case 'e': case 'E':
				case 'g': case 'G':

					dval = va_arg(ap, double);
					printf(conv, dval);
					break;

				case 'p':

					pval = va_arg(ap, void *);
					printf(conv, pval);
					break;
		
				case '%':

					putchar('%');
					break;

				default: 

					printf("%s", conv);
					break;

			}

		}
	
	va_end(ap);
}

int main () 

{
	minprintf(":%s:\n", "hello, world");
	minprintf(":%10s:\n", "hello, world");
	minprintf(":%.10s:\n", "hello, world");
	minprintf(":%-10s:\n", "hello, world");
	minprintf(":%.15s:\n", "hello, world");
	minprintf(":%-15s:\n", "hello, world");
	minprintf(":%15.10s:\n", "hello, world");
	minprintf(":%-15.10s:\n", "hello, world");

	minprintf("%e\n", 3.1415926535);
	minprintf("%f\n", 3.1415926535);
	minprintf("%g\n", 3.1415926535);

	return 0;
}
