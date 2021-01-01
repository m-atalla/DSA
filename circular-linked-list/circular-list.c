#include <stdlib.h>
#include <stdio.h>
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
} circular_list_t;

/**
 * 
 * Initialized circular list where the tail point at the head.
 */
void init_list(circular_list_t *list, int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->data = value;

    list->head = list->tail = node;

    list->head->next = list->tail;

    list->tail->next = list->head;
}

/**
 * 
 * enqueue to the end of the list.
 */
void append_list(circular_list_t *list, int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->data = value;

    node->next = list->head;

    list->tail->next = node;

    list->tail = node;
}

/**
 * 
 * Prints data of a circular list.
 */
void display(circular_list_t *list)
{
    node_t *current = list->head;

    do
    {
        printf("%d\n", current->data);

        current = current->next;
    } while (current != list->head);
}

/**
 * 
 * Removes duplicates in a sorted circular linked list.
 */
void remove_list_duplicates(circular_list_t *list)
{
    node_t *current = list->head;

    bool has_duplicates;

    do
    {
        // Initialize/reset flag
        has_duplicates = false;
        do
        {
            // Search for duplicates
            if (current->data == current->next->data)
            {
                node_t *duplicate = current->next;

                // Skip duplicate node in list.
                current->next = current->next->next;

                // Handles the case of the tail being the duplicate node
                if (duplicate == list->tail)
                {
                    list->tail = current;
                }

                // free duplicated node memory
                free(duplicate);

                // Toggle duplicates flag.
                has_duplicates = true;
            }

            current = current->next;
        } while (current != list->head);

    } while (has_duplicates);
}

int main()
{
    circular_list_t list = {NULL, NULL};

    init_list(&list, 5);

    // Appends duplicates
    for (size_t i = 0; i < 10; i++)
    {
        append_list(&list, (i + 1) * 5);
        append_list(&list, (i + 1) * 5);
    }

    remove_list_duplicates(&list);

    display(&list);

    return 0;
}
