#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int minscanf (char *fmt, ...)

{
	va_list	ap;
	char	*p, *q, conv[256];
	int	n, no_store, r;

	va_start(ap, fmt);
	p = fmt;
 	n = 0;
	while (*p != '\0') {

		no_store = 0;
		q = conv;
		for ( ; ; ) {

			while (*p != '%' && *p != '\0')
		
				*q++ = *p++;

			if (*p == '%') {
		
				*q++ = *p++;
				if (*p == '*') {

					*q++ = *p++;
					no_store = !0;

				} 

				while (isdigit(*p))

					*q++ = *p++;

				if (*p == 'h' || *p == 'l' || *p == 'L')

					*q++ = *p++;
				
				if ((*q++ = *p) == '%')

					p++;

				else

					break;

			} else

				break;

		}
		*q = '\0';

		if (no_store)

			r = scanf(conv);

		else 

			switch (*p) {

				case 'd': 
				case 'i': 
				case 'o': 
				case 'u': 
				case 'x':

					if (*(q - 2) == 'h') {
						
						short	*sp;

						sp = va_arg(ap, short *);
						r = scanf(conv, sp);

					} else if (*(q - 2) == 'l') {

						long	*lp;
						
						lp = va_arg(ap, long *);
						r = scanf(conv, lp);

					} else {

						int	*ip;

						ip = va_arg(ap, int *);
						r = scanf(conv, ip);

					}
					break;

				case 'c': 
				case 's': {

					char	*cp;

					cp = va_arg(ap, char *);
					r = scanf(conv, cp);

					break;

				}

				case 'e': 
				case 'f': 
				case 'g':

					if (*(q - 2) == 'l') {

						double	*dp;

						dp = va_arg(ap, double *);
						r = scanf(conv, dp);

					} else if (*(q - 2) == 'L') {

						long double 	*ldp;
	
						ldp = va_arg(ap, 
							long double *);
						r = scanf(conv, ldp);

					} else {

						float	*fp;

						fp = va_arg(ap, float *);
						r = scanf(conv, fp);

					}
					break;

				case '\0': 
				default:

					r = scanf(conv);
					break;

			}

		if (r == EOF) {

			n = EOF;
			break;

		} else if (r == 0)

			break;

		else

			n += r;

		if (*p != '\0')

			p++;

	}
	va_end(ap);

	return n;
}

int main ()

{
	int	c;

	/* To test, type "aaa%bbb 123" for example.  This will make minscanf() 
	 * read 123. 
	 */

	printf("minscanf() returned %d ", minscanf("a aa%%b bb%d", &c));
	printf("and read %d.\n", c);

	return 0;
}
