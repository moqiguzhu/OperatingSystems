#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

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

pthread_cond_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);
        while(count == MAX)
            pthread_cond_wait(&empty, &mutex);
        put(i);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}

void *consumer(void *arg)
{
    int i;
    for(i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);
        while(count == 0)
            pthread_cond_wait(&full, &mutex);
        int tmp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("current number : %d\n", tmp);
    }

    return 0;

}



int main()
{
    pthread_t p, c;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
