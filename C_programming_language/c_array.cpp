#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double get_avg(int arr[], int size)
{
	double res = 0;
	for(int i = 0; i < size; i++)
	{
		res += arr[i];
	}

	return res / size;
}

// C do not advocate return address of local variable to out of function
// if r is not static, the result print in function and out of function will be different
int * get_rand()
{
	static int r[10];

	srand((unsigned) time(NULL));

	for(int i = 0; i < 10; i++)
	{
		r[i] = rand();
		printf("%d ", r[i]);

	}
	printf("\n");


	return r;
}

int main()
{
	int arr[] = {1,2,3,4,5};

	double res = get_avg(arr, 5);
	printf("the average of elements in arr is : %f\n", res);
	
	int *p = arr;
	for(int i = 0; i < 5; i++)
	{
		printf("%d ", *(p+i));
	}
	printf("\n");

	int *p1 = get_rand();
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", *(p1+i));
	}
	printf("\n");

	return 0;
}
