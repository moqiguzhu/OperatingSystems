#include <stdio.h>

int main()
{
	int x = 1;
	int *p = &x;
	printf("%p\n", p);
	printf("%p\n", p+1);
	return 0;
}
