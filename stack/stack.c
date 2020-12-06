#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int top;
    int size;
} stack_t;

bool is_full(stack_t *stack);

void push(stack_t *stack, int value);

bool is_empty(stack_t *stack);



/**
 * 
 * Initializes stack.
 * 
 */
void init_stack(stack_t *stack, int size)
{
    stack->data = malloc(size * sizeof(int));

    stack->top = -1;

    stack->size = size;
}

/**
 * 
 * Frees memory
 * 
 */
void clear_stack(stack_t *stack)
{
    stack->top = -1;
    stack->size = 0;
    free(stack->data);
}

/**
 * 
 * Push a element to the top of the stack.
 * 
 */
void push(stack_t *stack, int value)
{
    if (is_full(stack))
    {
        printf("Overflow!\n");
    }else {
        stack->top++;

        stack->data[stack->top] = value;
    }
}

/**
 * 
 * Pop an element from the top of the stack.
 * 
 */
int pop(stack_t *stack)
{
    if (is_empty(stack))
    {
        printf("Underflow!\n");

        return -1;
    }

    int removeVal = stack->data[stack->top];

    stack->top--;

    return removeVal;
}

/**
 * 
 * Pop validation. Matigates underflow.
 * 
 */
bool is_empty(stack_t *stack)
{
    return stack->top < 0;
}

/**
 *
 * Prints stack starting from top. 
 * 
 */
void print_stack(stack_t *stack)
{
    for (int i = stack->top; i >= 0; i--)
        printf("%d\n", stack->data[i]);
}

/**
 * 
 * Push validation. Matigates overflow.
 * 
 */
bool is_full(stack_t *stack)
{
    return (stack->top  + 1) == stack->size;
}


/**
 * 
 * Searches a stack (haystack) to find a target (needle)
 * 
 * - Create a temp container can be: (Stack|Array)           
 * - Initialize a pop counter to avoid underflows in temp_stack.
 * - pop haystack -> check popped value for equality with needles -> push to temp container
 * - pop values in temp container push back to the haystack.
 * - free temp container (stack)
 */
void remove_by_value(stack_t *haystack, int needle)
{
    stack_t temp_stack;

    int pop_counter = 0;

    init_stack(&temp_stack, haystack->size);

    // Linear search
    for (int i = 0; i < haystack->size; i++)
    {
        int temp_value = pop(haystack);

        if (needle == temp_value)
        {
            printf("Needle found and removed. \n");
            break;
        }

        push(&temp_stack, temp_value);

        pop_counter++;
    }
    
    // Rerrange stack.
    for (int i = 0; i < pop_counter; i++)
        push(haystack, pop(&temp_stack));

    clear_stack(&temp_stack);
}


int main() {
    stack_t stack;

    int size = 10;

    init_stack(&stack, size);   

    // Filling stack with value
    for (int i = 0; i < size; i++)
        push(&stack, (i+1) * 10);

    // Print filled stack structure
    print_stack(&stack);

    printf("Finding removing some values:\n");

    remove_by_value(&stack, 20);

    remove_by_value(&stack, 30);

    remove_by_value(&stack, 40);

    // Printing modified stack
    print_stack(&stack);

    clear_stack(&stack);
}

