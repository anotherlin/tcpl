#include <ctype.h>
#include <stdio.h>

double atof (char s[])

{
	double	val, power;
	int	i, sign, esign, e;

	for (i = 0; isspace(s[i]); i++)

		;

	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')

		i++;

	for (val = 0.0; isdigit(s[i]); i++)

		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')

		i++;

	for (power = 1.0; isdigit(s[i]); i++) {

		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;

	}

	if (tolower(s[i]) == 'e') {

		esign = s[++i] == '-' ? -1 : 1;
		if (s[i] == '-' || s[i] == '+')

			i++;

		for (e = 0; isdigit(s[i]); i++)

			e = e * 10 + s[i] - '0';

		if (esign < 0)

			for (i = 0; i < e; i++)

				power *= 10.0;

		else

			for (i = 0; i < e; i++)

				power /= 10.0;

	}

	return sign * val / power;
}

int main ()

{
	printf("%g\n", atof("123.45e-6"));
	return 0;
}
