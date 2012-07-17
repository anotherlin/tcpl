#include <stdio.h>
#include <string.h>

void itoa (int n, char s[])

{
	int	l;
	
	if (n / 10 != 0)
	
		itoa(n / 10, s);
		
	else
		
		s[0] = '\0';

	l = strlen(s);
	s[l] = '0' + n % 10;
	s[l + 1] = '\0';
}

#define BUFFER_SIZE	16
#define TEST_VALUE	32100123

int main ()

{
	char	s[BUFFER_SIZE];

	itoa(TEST_VALUE, s);
	printf("itoa(%d) = %s\n", TEST_VALUE, s);
	return 0;
}
