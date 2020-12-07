#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int *data;
    int size;
    int end;
} queue_t;

bool is_empty(queue_t*);
bool is_full(queue_t*);

/**
 * 
 * Initializes queue struct.
 * 
 */
void init_queue(queue_t *queue, int size)
{
    queue->data = malloc(size * sizeof(size));
    
    queue->size = size;

    queue->end = -1;
}

/**
 * 
 * Add an element to the end of the queue.
 * 
 */
void enqueue(queue_t *queue, int value)
{
    if (is_full(queue))
    {
        printf("Overflow! while attempting to enqueue: %d\n", value);
        exit(0);
    }
    
    queue->end++;

    queue->data[queue->end] = value;
}

/**
 * 
 * remove an element from the front of the queue
 * 
 */
int dequeue(queue_t *queue)
{
    if (is_empty(queue))
    {
        printf("Underflow! the queue is empty.\n");
        exit(0);
    }
    int dequeuedVal = queue->data[0];

    queue->end--;
    
    // Shift queue one index forward.
    for (int i = 0; i <= queue->end; i++)
        queue->data[i] = queue->data[i + 1];
    
    // return the dequeued value
    return dequeuedVal;
}

/**
 *
 * Free memory
 *  
 */
void free_queue(queue_t *queue)
{
    free(queue->data);
    queue->size = 0;
    queue->end = -1;
}

/**
 *
 * Overflow validation. 
 *
 */
bool is_full(queue_t *queue)
{
    return queue->end + 1 == queue->size;
}

/**
 * 
 * Underflow validation.
 *  
 */
bool is_empty(queue_t *queue)
{
    return queue->end < 0;
}

/**
 *
 * Leftmost value is first in queue. 
 * 
 */
void print_queue(queue_t *queue) 
{
    printf("%d", queue->data[0]);
    for (int i = 1; i <= queue->end; i++)    
        printf(" <== %d", queue->data[i]);

    printf("\n");
}

int main()
{
    queue_t queue;

    init_queue(&queue, 5);

    // Filling queue
    enqueue(&queue, 9);
    enqueue(&queue, 5);
    enqueue(&queue, 65);
    enqueue(&queue, 821);
    enqueue(&queue, 7);

    dequeue(&queue);

    print_queue(&queue);
   
    free_queue(&queue);
}