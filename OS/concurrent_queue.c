#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

typedef struct __node_t
{
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t
{
    node_t *head;
    node_t *tail;
    pthread_mutex_t headlock;
    pthread_mutex_t taillock;
} queue_t;

void queue_init(queue_t *q)
{
    node_t *tmp = malloc(sizeof *tmp);
    tmp->next = NULL;
    q->head = q->tail = tmp;        // sentinel node
    pthread_mutex_init(&q->headlock, NULL);
    pthread_mutex_init(&q->taillock, NULL);
}

void queue_enqueue(queue_t *q, int value)
{
    // memory allocate operation should be out of critical section
    node_t *tmp = malloc(sizeof *tmp);
    assert(tmp != NULL);
    
    tmp->value = value;
    tmp->next = NULL;

    pthread_mutex_lock(&q->taillock);
    q->tail->next = tmp;
    q->tail = tmp;
    pthread_mutex_unlock(&q->taillock);
}

int queue_dequeue(queue_t *q, int *value)
{
    pthread_mutex_lock(&q->headlock);
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if(new_head == NULL)
    {
        pthread_mutex_unlock(&q->headlock);
        return -1;      // queue was empty
    }
    *value = new_head->value;
    q->head = new_head;
    pthread_mutex_unlock(&q->headlock);
    free(tmp);

    return 0;
}

int main()
{
    return 0;
}
