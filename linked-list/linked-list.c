#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
} list_t;

void init_list(list_t *list, int init_value)
{
    list->head = (node_t *)malloc(sizeof(node_t));

    list->head->data = init_value;

    list->head->next = NULL;

    list->tail = list->head;
}

/**
 * 
 * Adds a node to the end of a list.
 */
void append_list(list_t *list, int val)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));

    temp->data = val;

    temp->next = NULL;

    list->tail->next = temp;

    list->tail = temp;
}

/**
 * 
 * Frees every node in a list.
 */
void free_list(list_t *list)
{
    if (list->head == list->tail)
    {
        free(list->head);
        return;
    }

    node_t *current = list->head;

    while (current != NULL)
    {
        node_t *prev = current;

        current = current->next;

        free(prev);
    }
}

/**
 * 
 * Prints contents of a list.
 */
void print_list(list_t *list)
{
    node_t *current = list->head;

    while (current != NULL)
    {
        if (current == list->head)
        {
            printf("---\n%d<- head \n", current->data);
        }
        else if (current == list->tail)
        {
            printf("%d<- tail\n---\n", current->data);
        }
        else
        {
            printf("%d \n", current->data);
        }

        current = current->next;
    }
}

int max_in_list(list_t *list)
{
    node_t *current = list->head;

    int max = current->data;

    while (current != NULL)
    {
        if (current->data > max)
        {
            max = current->data;
        }

        current = current->next;
    }

    return max;
}

int min_in_list(list_t *list)
{
    node_t *current = list->head;

    int min = current->data;

    while (current != NULL)
    {
        if (current->data < min)
        {
            min = current->data;
        }

        current = current->next;
    }

    return min;
}

int avg_in_list(list_t *list)
{
    node_t *current = list->head;

    int sum = 0;

    int count = 0;

    while (current != NULL)
    {
        sum += current->data;

        count++;

        current = current->next;
    }

    return sum / count;
}

int count_list_evens(list_t *list)
{
    node_t *current = list->head;

    int even_count = 0;

    while (current != NULL)
    {
        if (current->data % 2 == 0)
        {
            even_count++;
        }

        current = current->next;
    }

    return even_count;
}

void merge(list_t *src_a, list_t *src_b, list_t *dist_list)
{
    init_list(dist_list, src_a->head->data);

    node_t *current = src_a->head->next;

    while (current != NULL)
    {
        append_list(dist_list, current->data);

        // When reaching the end of the first set..
        // Set current to src_b head
        if (current->next == NULL && current->data == src_a->tail->data)
        {
            current = src_b->head;
            continue;
        }

        current = current->next;
    }
}

void reverse(list_t *list)
{
    node_t *current = list->head;

    list->head = list->tail;

    list->tail = current;

    node_t *prev = NULL;

    while (current != NULL)
    {
        node_t *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
}

/**
 * 
 * Bubble sort.
 */
void sort(list_t *list)
{
    bool swap;

    do
    {
        node_t *current = list->head;

        swap = false;

        while (current != NULL)
        {
            if (current->next != NULL && current->data > current->next->data)
            {
                int temp = current->data;

                current->data = current->next->data;

                current->next->data = temp;

                swap = true;
            }
            current = current->next;
        }
    } while (swap);
}

void remove_duplicates(list_t *list)
{
    node_t *current = list->head;

    while (current != NULL)
    {
        if (current->next != NULL && current->data == current->next->data)
        {
            node_t *duplicate = current->next;

            current->next = current->next->next;

            free(duplicate);
        }

        current = current->next;
    }
}

int main()
{
    list_t list_0 = {NULL, NULL};

    list_t list_1 = {NULL, NULL};

    list_t merge_list = {NULL, NULL};

    int rand[] = {9, 2, 5, 11, 9, 5, 2};

    init_list(&list_0, 20);

    init_list(&list_1, 99);

    for (size_t i = 0; i < sizeof(rand) / sizeof(int); i++)
    {
        append_list(&list_0, rand[i]);

        append_list(&list_1, rand[i] * 2);
    }

    print_list(&list_0);

    //? Questions 1 and two.
    // Max, min and average of a list.
    printf("Max: %d\n", max_in_list(&list_0));

    printf("Min: %d\n", min_in_list(&list_0));

    printf("Avg: %d\n---\n", avg_in_list(&list_0));

    // Even numbers in a list
    printf("Even numbers count: %d\n---\n", count_list_evens(&list_0));

    // merging list.
    merge(&list_0, &list_1, &merge_list);

    reverse(&merge_list);

    sort(&merge_list);

    //? Question 3, 4 and 5
    printf("Merged, reversed and sorted list: ");

    print_list(&merge_list);

    //? Question 6 - Given a sorted list remove duplicate nodes.
    sort(&list_0);

    remove_duplicates(&list_0);

    print_list(&list_0);

    free_list(&list_0);
    free_list(&list_1);
    free_list(&merge_list);
    return 0;
}
