#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#include "concurrent_list.h"

#define BUCKETS (101)

typedef struct __hash_t
{
    list_t lists[BUCKETS];
} hash_t;

void hash_init(hash_t *t)
{
    int i;
    for(i = 0; i < BUCKETS; i++)
    {
        list_init(&t->lists[i]);
    }
}

int hash_insert(hash_t *t, int key)
{
    int bucket = key % BUCKETS;
    return list_insert(&t->lists[bucket], key);
}

int hash_lookup(hash_t *t, int key)
{
    int bucket = key % BUCKETS;
    return list_lookup(&t->lists[bucket], key);
}

int main()
{
    return 0;
}
