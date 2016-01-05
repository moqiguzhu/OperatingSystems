#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //
#include <semaphore.h>

// constants
#define NUM_READERS 5
#define NUM_WRITERS 5
#define NUM_READS 5
#define NUM_WRITES 5

// global data
unsigned int shared_val = 0;

typedef struct _rwlock_t
{
    sem_t lock;
    sem_t writelock;
    int readers;
} rwlock_t;

rwlock_t rw;

void rwlock_init(rwlock_t *rw)
{
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw)
{
    sem_wait(&rw->lock);
    rw->readers++;
    if(rw->readers == 1)
        sem_wait(&rw->writelock);
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw)
{
    sem_wait(&rw->lock);
    rw->readers--;
    if(rw->readers == 0)
        sem_post(&rw->writelock);
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw)
{
    sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw)
{
    sem_post(&rw->writelock);
}

void *read_main(void *arg)
{
    int num = *((int*)arg);
    sem_wait(&rw.lock);
    rw.readers++;
    if(rw.readers == 1)
        sem_wait(&rw.writelock);

    printf("%d reader read the shared val: %d\n", num, shared_val);
    
    rw.readers--;
    if(rw.readers == 0)
        sem_post(&rw.writelock);
    sem_post(&rw.lock);

    pthread_exit(0);
}

void *write_main(void *arg)
{
    int num = *((int*)arg);
    sem_wait(&rw.writelock);
    shared_val++;

    printf("%d writer write the shared val: %d\n", num, shared_val);
    
    sem_post(&rw.writelock);

    pthread_exit(0);
}

int main()
{
    int i;
    int reader_num[NUM_READERS];
    int writer_num[NUM_WRITERS];

    pthread_t reader_thread_ids[NUM_READERS];
    pthread_t writer_thread_ids[NUM_WRITERS];

    rwlock_init(&rw);


    for(i = 0; i < NUM_READERS; i++)
    {
        reader_num[i] = i;
        pthread_create(&reader_thread_ids[i], NULL, read_main, &reader_num[i]);
    }

    for(i = 0; i < NUM_WRITERS; i++)
    {
        writer_num[i] = i;
        pthread_create(&writer_thread_ids[i], NULL, write_main, &writer_num[i]);
    }

    for(i = 0; i < NUM_READERS; i++)
    {
        pthread_join(reader_thread_ids[i], NULL);
    }

    for(i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writer_thread_ids[i], NULL);
    }

    return 0;
}
