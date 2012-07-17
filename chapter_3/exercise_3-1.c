#include <stdio.h>

int binsearch (int x, int v[], int n)

{
	int	low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {

		/* The tricky part here is the way mid is computed, which is 
		 * actually floor((low + high) / 2).  This must be kept in mind
 		 * to make sure that the interval actually shrinks to only one
		 * element during the loop.  As only one compare is made 
		 * instead of two, this version is faster.
		 */

		mid = (low + high) / 2;
		if (x > v[mid])

			low = mid + 1;

		else 

			high = mid;

	}

	if (v[low] == x)

		return low;

	else

		return -1;
}

#define N	11

int V[N] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 31 };

int main ()

{
	printf("%d\n", binsearch(7, V, N));
	printf("%d\n", binsearch(8, V, N));
	return 0;
}

