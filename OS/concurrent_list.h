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

void list_init(list_t *l);

int list_insert(list_t *l, int key);

int list_lookup(list_t *l, int key);
