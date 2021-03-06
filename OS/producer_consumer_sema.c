#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#define MAX 4

int buffer[MAX];
int fill = 0;
int use = 0;
int count = 0;

int loops = 100;

void put(int value)
{
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    count++;
}

int get()
{
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    count--;

    return tmp;
}

sem_t empty;
sem_t full;

// this function could only support one thread
void *producer(void *arg)
{
    int i;
    for(i = 0; i < loops; i++)
    {
        sem_wait(&empty);
        put(i);
        sem_post(&full);
    }

    return 0;
}

// this function could only support one thread
void *consumer(void *arg)
{
    int i, tmp = 0;
    for(i = 0; i < loops; i++)
    {
        sem_wait(&full);
        tmp = get();
        sem_post(&empty);
        printf("current number : %d\n", tmp);
    }

    return 0;
}

int main()
{
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);

    pthread_t p, c;

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
