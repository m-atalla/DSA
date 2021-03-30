#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    char data;
    struct node * next;
}node_t;

typedef struct tree_node
{
    char data;
    struct tree_node * left;
    struct tree_node * right;
}tree_node_t;

typedef struct 
{
    node_t *front;
    node_t *rear;
}queue_t;

node_t * create_node(char c) {
    node_t * new_node = malloc(sizeof(node_t));
    new_node->data = c;
    new_node->next = NULL;

    return new_node;
}
queue_t* init_queue(){
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    queue->front = queue->rear = NULL;
    return queue;
}
void enqueue(queue_t *q, char c) {
    // Skip whitespace from the queue
    if (c == ' ') return;

    // empty queue
    if (q->front == NULL)
    {
        q->front = q->rear = create_node(c);
    }
    else
    {
        node_t * new_node = create_node(c);

        q->rear->next = new_node;

        q->rear = new_node;
    }
    
    
}

char dequeue(queue_t *q) {
    if (q->rear == NULL)
    {
        fprintf(stderr,"Underflow\n");
        exit(0);
    }

    if (q->front == q->rear)
    {
        char deq_value = q->rear->data;

        node_t * dangling_ptr = q->rear;

        q->front = q->rear = NULL;

        free(dangling_ptr);

        return deq_value;
    }
    
    
    char deq_value = q->front->data;

    node_t * temp = q->front;

    q->front = temp->next; // Shift queue front

    free(temp); // free dangling pointer

    return deq_value;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

tree_node_t * create_tree_node(char root_val) {
    tree_node_t * root = malloc(sizeof(tree_node_t));
    root->data = root_val;
    root->left = root->right = NULL;
}

/**
 * operator precedence
 */
int precedence(tree_node_t * node) {
    if (node->data == '+' || node->data == '-') return 2;

    if (node->data == '*' || node->data == '/') return 1;

    return 0;
}

tree_node_t * build_tree(char *exp, queue_t * queue_buffer, int index) {
    // Skip whitespaces
    if (exp[index] == ' ') ++index;


    // Reaching end of the string (end case)
    if (exp[index] == '\0') return create_tree_node(dequeue(queue_buffer));
    

    // Enqueue operands to the buffer
    if (!isOperator(exp[index])){
        enqueue(queue_buffer, exp[index]);
        
        // To the next operator... A + B
        return build_tree(exp, queue_buffer, ++index);
    }
    
    // Evaluate queue and evaluate whatever is on the right.
    if (isOperator(exp[index]))
    {
        tree_node_t * root = create_tree_node(exp[index]);

        root->left = create_tree_node(dequeue(queue_buffer));

        root->right = build_tree(exp, queue_buffer, ++index);

        // Validates order of operations
        if (precedence(root->right) > precedence(root))
        {
            tree_node_t * validated_root = root->right;

            root->right = validated_root->left;

            validated_root->left = root;
            
            // Validated subtree root
            return validated_root;
        }
        else
        {
            return root;
        }
    }      
}


void infix_print(tree_node_t * root) {
    if (root != NULL)
    {
        infix_print(root->left);

        printf(" %c ", root->data);

        infix_print(root->right);
    }
    
}
/**
 * print expression tree in postfix order
 * A + B => A B +
 */
void postfix_print(tree_node_t *root) {
    if (root != NULL)
    {
        postfix_print(root->left);
       
        postfix_print(root->right);

        printf(" %c ", root->data);
    }
}

int main ()
{
    char * infix = "A * B + C / D";

    queue_t * q_b = init_queue();
    tree_node_t *exp_tree = build_tree(infix, q_b, 0);

    printf("Infix: ");
    infix_print(exp_tree);
    printf("\n");

    printf("Postfix: ");
    postfix_print(exp_tree);
    printf("\n");

    return 0;
}