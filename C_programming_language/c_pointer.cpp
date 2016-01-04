#include <stdio.h>

int main()
{
	int *ptr = NULL;
	printf("The value of ptr is : %x\n", (unsigned int)ptr);

	if(!ptr)
	{
		printf("the ptr is a empty pointer! \n");
	}


	return 0;
}

