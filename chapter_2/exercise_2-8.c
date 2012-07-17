#include <limits.h>
#include <stdio.h>

unsigned rightrot (unsigned x, int n)

{
	return (x << ((sizeof(unsigned) * CHAR_BIT) - n)) | (x >> n);
}

int main ()

{
	unsigned	x, y;

	x = 0x10;
	printf("rightrot(0x%08x, 3) = 0x%08x\n", x, y = rightrot(x, 3));
	x = y;
	printf("rightrot(0x%08x, 3) = 0x%08x\n", x, y = rightrot(x, 3));

	return 0;
}
