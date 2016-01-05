#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5


void *hello(void *arg)
{
	printf("Hello Thread \n");
	return 0;
}

void *thread_func(void *arg)
{
	int private_key = *(int*)arg;
	printf("Thread number is %d\n", private_key);

	return 0;
}

int main()
{
	int i;
	pthread_t tid[NUM_THREADS];

    // error example
    // in this way, four thread have a shared variable i, but without synchronization control
//	for(i = 0; i < NUM_THREADS; i++)
//	{
//		pthread_create(&tid[i], NULL, thread_func, &i);
//	}

    int thread_nums[NUM_THREADS];
    for(i = 0; i < NUM_THREADS; i++)
    {
        thread_nums[i] = i;
        pthread_create(&tid[i], NULL, thread_func, &thread_nums[i]);
    }

	for(i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}

    return 0;
}
