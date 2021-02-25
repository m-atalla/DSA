/** Open addressing collsion **/
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int capacity;
    int *array;
} OA_hash_t;


OA_hash_t * create_table(int s) 
{
    OA_hash_t * htable = malloc(sizeof(OA_hash_t));
    htable->capacity = s;
    htable->array = malloc(sizeof(int) * htable->capacity);

    for (int i = 0; i < htable->capacity; i++)
    {
        htable->array[i] = -1;
    }

    return htable;
}

int check_collision(OA_hash_t* ht, int x) 
{
    return !(ht->array[x] == -1);
}

int hash(int capacity,int x) {
    return (x % capacity);
}

int double_tap_hash(int capacity,int x) 
{
    return (7 - (x % capacity));
}

int linear_probing(OA_hash_t * htable, int hash_val, int i) 
{
    return ((hash_val + i) % htable->capacity);
}

/**
 * Add an item using linear probing
 */
void add_lp(OA_hash_t * htable, int val) 
{
    int hash_val = hash(htable->capacity, val);

    int i = 0;
    int hashkey;

    while (check_collision(htable, hashkey = linear_probing(htable, hash_val, i)))
    {
        if (i > htable->capacity)
        {
            printf("Maximum collisions dedicted. can't add [%d] to the table\n", val);
            return;
        }
        
        i++;
    }

    htable->array[hashkey] = val;
}


void print_table(OA_hash_t * ht) 
{
    for (int i = 0; i < ht->capacity; i++)
    {
        printf("[%d]: ", i);

        if (ht->array[i] == -1)
        {
            printf("nil");
        } 
        else
        {
            printf("%d", ht->array[i]);
        }
        
        printf("\n");
    }
}

int main()
{
    #pragma linearprobing 
    OA_hash_t * htable = create_table(10);
        add_lp(htable, 89);
        add_lp(htable, 18);
        add_lp(htable, 49);
        add_lp(htable, 58);
        add_lp(htable, 69); // nice
        add_lp(htable, 99);
        add_lp(htable, 99);
        add_lp(htable, 99);
        add_lp(htable, 99);
    #pragma endlinearprobing

    print_table(htable);
    return 0;
}
