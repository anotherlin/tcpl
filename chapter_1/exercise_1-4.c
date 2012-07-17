#include <stdio.h>

main ()

{
	int	celcius, fahr;
	int	lower, upper, step;

	/* No floating-point needed with the following settings: */

	lower = -20;
	upper = 100;
	step = 10;	

	celcius = lower;
	while (celcius <= upper) {

		fahr = 9 * celcius / 5 + 32;
		printf("%3d %3d\n", celcius, fahr);
		celcius = celcius + step;

	}
}
