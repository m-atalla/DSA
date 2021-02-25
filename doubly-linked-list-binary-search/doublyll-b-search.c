#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
} list_t;

/**
 * Initialize a list with a single node
 * @param init_value node data
 * NULL <-[head=tail]-> NULL
 */
void init_list(list_t *list, int init_value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = init_value;
    node->prev = NULL;
    node->next = NULL;

    list->head = node;
    list->tail = node;
}

/**
 * 
 * Append a new tail
 */
void append(list_t *list, int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->data = value;

    node->next = NULL;

    node->prev = list->tail;

    list->tail->next = node;

    list->tail = node;
}

/**
 * 
 * prepend a new head
 */
void prepend(list_t *list, int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->data = value;

    node->prev = NULL;

    node->next = list->head;

    list->head->prev = node;

    list->head = node;
}

/**
 * 
 * 
 */
void display(list_t *list)
{
    node_t *curr = list->head;

    while (curr != NULL)
    {
        printf("%d\n", curr->data);

        curr = curr->next;
    }
}

void sort(list_t *list)
{
    bool is_sorted = true;

    while (is_sorted)
    {
        is_sorted = false;

        node_t *curr = list->head;

        while (curr != NULL)
        {
            if (curr->next != NULL && curr->data > curr->next->data)
            {
                int temp = curr->data;

                curr->data = curr->next->data;

                curr->next->data = temp;

                is_sorted = true;
            }

            curr = curr->next;
        }
    }
}


/**
 * Finding mid node using two pointers `slow` and `fast`
 * Fast pointer moves twice as fast as the slow pointer
 * e.g.: slow = slow->next | fast = fast->next->next
 * Fast pointer should stop when reaching the tail node.
 * 
 */
node_t * find_mid(list_t *list) 
{
    node_t *slow;
    node_t *fast;

    slow = fast = list->head;

    while (fast != list->tail)
    {
        fast = fast->next;

        // break down fast->next->next on the fast pointer
        // to avoid dereference a null pointer by calling `->next` on '0x0'
        // which causes a segmentation fault
        if (fast != list->tail)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    return slow;
}

/**
 * 
 * 
 */
void binary_search(list_t *list, int search_term, bool is_sorted) 
{
    // avoid repeating redundant sorting during recursion
    if (!is_sorted)
    {
        sort(list);
    }
    
    node_t * mid = find_mid(list);

    if (mid->data == search_term)
    {
        printf("Found!\n");
        return;
    }

    if (mid->next == NULL || mid->prev == NULL)
    {
        printf("Not Found!\n");
        return;
    }

    if (search_term > mid->data)
    {
        // Exclude the mid point from head and pass
        list_t list_split = {mid->next, list->tail};

        binary_search(&list_split, search_term, true);
    }
    
    if (search_term < mid->data)
    {
        // Exclude mid node from tail and pass the split list
        list_t list_split = {list->head, mid->prev};
        
        binary_search(&list_split, search_term, true);
    }
}


int main()
{
    list_t list;

    init_list(&list, 5);

    append(&list, 20);

    append(&list, 1);

    binary_search(&list, 2, false);

    display(&list);
}