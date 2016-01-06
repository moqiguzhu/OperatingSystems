#include <stdio.h>
#include <pthread.h>

typedef struct __zem_t
{
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} zem_t;

void zem_init(zem_t *s, int value)
{
    s->value = value;
    pthread_cond_init(&s->cond, NULL);
    pthread_mutex_init(&s->lock, NULL);
}

// In this implementation, value can not be less than 0
// Is this semantic corresponding with original semaphore?
//
// the value of semaphore, when negative, is equal to number of waiting threads
void zem_wait(zem_t *s)
{
    pthread_mutex_lock(&s->lock);
    while(s->value <= 0)
        pthread_cond_wait(&s->cond, &s->lock);
    s->value--;
    pthread_mutex_unlock(&s->lock);
}

void zem_post(zem_t *s)
{
    pthread_mutex_lock(&s->lock);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}

