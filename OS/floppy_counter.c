#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4
#define COUNTER_SUM 400000

typedef struct __counter_t
{
    int global;
    pthread_mutex_t glock;
    int locals[NUM_THREADS];
    pthread_mutex_t llocks[NUM_THREADS];
    int threshold;
} counter_t;

counter_t *c;

void init(counter_t *c, int threshold)
{
    c->threshold = threshold;

    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);

    int i;
    for(i = 0; i < NUM_THREADS; i++)
    {
        c->locals[i] = 0;
        pthread_mutex_init(&c->llocks[i], NULL);
    }
}

void update(counter_t *c, int thread_id, int amt)
{
    pthread_mutex_lock(&c->llocks[thread_id]);
    c->locals[thread_id] += amt;
    if(c->locals[thread_id] >= c->threshold)
    {
        pthread_mutex_lock(&c->glock);
        c->global += c->locals[thread_id];
        pthread_mutex_unlock(&c->glock);
        c->locals[thread_id] = 0;
    }
    pthread_mutex_unlock(&c->llocks[thread_id]);
}

void mandate_update(counter_t *c, int thread_id)
{
    pthread_mutex_lock(&c->llocks[thread_id]);
    pthread_mutex_lock(&c->glock);

    c->global += c->locals[thread_id];
    c->locals[thread_id] = 0;

    pthread_mutex_unlock(&c->glock);
    pthread_mutex_unlock(&c->llocks[thread_id]);
}

int get(counter_t *c)
{
    int i;
    for(i = 0; i < NUM_THREADS; i++)
    {
        mandate_update(c, i);
    }

    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
   
    return val; 
}

void *main_update(void *arg)
{
    int val = get(c);
    while(val < COUNTER_SUM)
    {
        int thread_id = *((int*)arg);
        update(c, thread_id, 1);

        val = get(c);
    }

    return 0;
}

void *main_get()
{
    int val = get(c);
    while(val < COUNTER_SUM)
    {
        val = get(c);
        printf("current global counter is : %d\n", val);
    }

    printf("global counter : %d\n", val);
    
    return 0;
}


int main()
{
    c = malloc(sizeof *c);
    
    init(c, 100);
    
    pthread_t local_counters[NUM_THREADS];
    pthread_t global_counter;
    int local_nums[NUM_THREADS];

    pthread_create(&global_counter, NULL, main_get, NULL);
    int i;
    for(i = 0; i < NUM_THREADS; i++)
    {
        local_nums[i] = i;
        pthread_create(&local_counters[i], NULL, main_update, &local_nums[i]);
    }

    pthread_join(global_counter, NULL);
    for(i = 0; i < NUM_THREADS; i++)
        pthread_join(local_counters[i], NULL);

    return 0;
}
