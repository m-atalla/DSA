#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *data;
    int front, rear, size;
} queue_t;

void init_queue(queue_t *queue, int size)
{
    queue->data = (int *)malloc(size * sizeof(int));

    queue->front = queue->rear = -1;

    queue->size = size;
}

void free_queue(queue_t *queue)
{
    free(queue->data);

    // Not entirely sure if the following two statements are needed.
    queue->front = queue->rear = -1;

    queue->size = 0;
}

/**
 * 
 * Checks if a queue is full.
 */
bool is_full(queue_t *queue)
{
    return (queue->rear + 1) % queue->size == queue->front;
}

/**
 * 
 * Adds an item to the end of a queue.
 */
void enqueue(queue_t *queue, int val)
{
    if (is_full(queue))
    {
        fprintf(stderr, "Overflow!\n");
        return;
    }

    if (queue->front == -1)
    {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->size;

    queue->data[queue->rear] = val;
}

/**
 * 
 * Checks if a queue is empty.
 */
bool is_empty(queue_t *queue)
{
    return queue->front == -1;
}

/**
 * 
 * Removes an element from the front of the queue and returns its value.
 */
int dequeue(queue_t *queue)
{
    // Dequeue validation
    if (is_empty(queue))
    {
        fprintf(stderr, "Underflow!");
    }

    // Value to be returned
    int yield = queue->data[queue->front];

    // If queue front and queue rear are at the same index
    // That element must be the last element in the queue
    // Thus queue indexes need to be "reseted".
    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % queue->size;
    }

    return yield;
}

/**
 * 
 * Recursively reverse a queue abusing properties of the callstack.
 */
queue_t *reverse(queue_t *queue)
{
    // End case on the final
    if (queue->front == queue->rear)
    {
        int lastVal = dequeue(queue);

        enqueue(queue, lastVal);

        // Starts popping the stack when reaching end of the queue (rear)
        return queue;
    }

    // Carru dequeue in the stack till it is resolved.
    int carry = dequeue(queue);

    // Save a snapshot of the queue as a local variable on the stack.
    queue_t *snapshot = reverse(queue);

    enqueue(snapshot, carry);

    return snapshot;
}

/**
 * 
 * Removes the first ith element in a queue
 */
void remove_ith(queue_t *queue, int ith)
{
    queue_t temp_q;

    init_queue(&temp_q, queue->size);

    int count = 0;

    while (!is_empty(queue))
    {
        if (count == ith)
        {
            dequeue(queue);
            count++;
            continue;
        }

        enqueue(&temp_q, dequeue(queue));

        count++;
    }

    // Copy temp_q into queue
    // delete dangling pointer..

    int *danglingPtr = queue->data;

    queue->data = temp_q.data;

    queue->front = temp_q.front;

    queue->rear = temp_q.rear;

    queue->size = temp_q.size;

    free(danglingPtr);
}

/**
 * 
 * Dsiplays as if the circular queue was straightened out...
 */
void display(queue_t *queue)
{
    printf("\nFront -> [%d", queue->data[queue->front]);

    for (int i = queue->front + 1; i < queue->rear; i++)
        printf(" <== %d", queue->data[i]);

    printf(" <== %d] <- Rear \n\n", queue->data[queue->rear]);
}

int main()
{
    queue_t queue;

    init_queue(&queue, 5);

    for (size_t i = 0; i < queue.size; i++)
        enqueue(&queue, (i + 1) * 3);

    enqueue(&queue, 13);

    enqueue(&queue, 21);

    display(&queue);

    // 4 - Reversing queue elements
    reverse(&queue);

    //
    display(&queue);

    // 5 - Remove the first ith elements from a queue.
    remove_ith(&queue, 3);

    //
    display(&queue);

    return 0;
}
