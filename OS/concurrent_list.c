/********************************************
 * we can also implement a more fined lock.
 * add a lock for every node in list, but this kind of 
 * strategy will add overhead greatly and is not efficient
 * when compared with pure single lock stategy
 * ******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct __node_t
{
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t
{
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void list_init(list_t *l)
{
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

// move codes about memory allocate out of critical section
int list_insert(list_t *l, int key)
{
    node_t *new = malloc(sizeof *new);
    if(new == NULL)
    {
        perror("malloc");   // memory allocate error
        return -1;          // insert failsure
    }
    new->key = key;
 
    // begining of critical section
    pthread_mutex_lock(&l->lock);
    new->next = l->head;
    l->head = new;
    pthread_mutex_unlock(&l->lock);

    return 0;           // insert success
}

// using a variable rv, same procedure with lookup successful or unsuccessful
int list_lookup(list_t *l, int key)
{
    int rv = -1;
    pthread_mutex_lock(&l->lock);
    node_t *curr = l->head;
    while(curr)
    {
        if(curr->key == key)
        {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_lock(&l->lock);

    return rv;
}

int main()
{
    return 0;
}
