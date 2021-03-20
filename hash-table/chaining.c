#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;

    struct node *chain;
}node_t;

typedef struct 
{
    int size;
    node_t **list;
}hash_table_t;


hash_table_t * create_table(int size)
{
    hash_table_t * ht = malloc(sizeof(hash_table_t));
    ht->list = malloc(sizeof(node_t) * size);
    ht->size = size;

    for (int i = 0; i < size; i++)
        ht->list[i] = NULL;
    
    
    return ht;
}   

int hash(hash_table_t *ht, int x) 
{
    return (x % ht->size);
}

void insert(hash_table_t *ht, int val) 
{
    int index = hash(ht, val);

    node_t * link = (node_t *) malloc(sizeof(node_t));
    link->data = val;
    link->chain = NULL;

    node_t * curr = ht->list[index];

    if (curr == NULL)
    {
        ht->list[index] = link;
        return;
    }
    
    while (curr->chain != NULL)
    {
        curr = curr->chain;
    }

    curr->chain = link;
}

void print_table(hash_table_t * ht) 
{
    for (int i = 0; i < ht->size; i++)
    {
        node_t * curr = ht->list[i];

        printf("[%d]: ", i);

        if (curr == NULL)
        {
            printf("nil");
        }
        
        while (curr)
        {
            printf("%d ", curr->data);
            curr = curr->chain;
        }

        printf("\n");
    }
}
int main()
{
    hash_table_t *ht = create_table(10);

    insert(ht, 89);
    insert(ht, 18);
    insert(ht, 49);
    insert(ht, 58);
    insert(ht, 69);
    insert(ht, 99);

    print_table(ht);
    return 0;
}

