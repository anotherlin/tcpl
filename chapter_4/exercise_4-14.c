#include <stdio.h>

#define SWAP(t, x, y) \
{\
	t	p;\
\
	p = x;\
	x = y;\
	y = p;\
\
}

int main ()

{
	int	x, y;

	x = 1;
	y = 2;
	printf("Before swap:\tx = %d, y = %d.\n", x, y);
	SWAP(int, x, y);
	printf("After swap:\tx = %d, y = %d.\n", x, y);

	return 0; 
}
