#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node_t;

/**
 * creates and returns a pointer to the new node.
 * 
 */
node_t *create_node(int data)
{
    node_t *node = (node_t *)malloc(sizeof(node));
    node->data = data;
    node->left = node->right = NULL;
}

/**
 * Insert a new value to a binary tree
 * 
 */
void insert_node(node_t **root, int value)
{
    if ((*root) == NULL)
    {
        *root = create_node(value);
        return;
    }
    else if (value <= (*root)->data)
    {
        insert_node(&(*root)->left, value);
    }
    else
    {
        insert_node(&(*root)->right, value);
    }
}
void print_tree_depth(node_t *root)
{
    if (root != NULL)
    {
        print_tree_depth(root->left);
        printf("%d\n", root->data);
        print_tree_depth(root->right);
    }
}

/**
 * Gets length of the tree
 * 
 */
int length(node_t *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int l_length = length(root->left);

        int r_length = length(root->right);

        if (l_length > r_length)
        {
            return (l_length + 1);
        }
        else
        {
            return (r_length + 1);
        }
    }
}
/**
 * Sums tree values the tree depth first traversal
 * 
 */
void sum_tree(node_t *root, int *carry)
{
    if (root != NULL)
    {
        (*carry) += root->data;
        sum_tree(root->left, carry);
        sum_tree(root->right, carry);
    }
}

/**
 * Finds maximum values depth first traversal
 * 
 */
void max_tree(node_t *root, int *max_carry)
{
    if (root != NULL)
    {
        if (root->data > (*max_carry))
        {
            (*max_carry) = root->data;
        }

        max_tree(root->left, max_carry);
        max_tree(root->right, max_carry);
    }
}

/**
 * Copy a tree using depth first tree traversal pre-order
 * 
 */
node_t *copy_tree(node_t *root)
{
    if (root == NULL)
        return NULL;

    node_t *copy = create_node(root->data);

    copy->left = copy_tree(root->left);

    copy->right = copy_tree(root->right);

    return copy;
}

bool check_identical_tree(node_t *tree1, node_t *tree2)
{

    // When reaching leaf nodes
    if (tree1 == NULL && tree2 == NULL)
    {
        return true;
    }

    if (tree1 != NULL && tree2 != NULL)
    {
        // Compare current node and all connected nodes
        return (
            (tree1->data == tree2->data) &&
            check_identical_tree(tree1->left, tree2->left) &&
            check_identical_tree(tree1->right, tree2->right));
    }

    // nodes are not equal
    return false;
}

/**
 * Free tree allocated memory using depth-first(postorder)
 * 
 */
void free_tree(node_t *root)
{
    if (root != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(int argc, char const *argv[])
{
    node_t *root = create_node(40);
    node_t *root_copy;
    int sum = 0;
    int max = 0;

    insert_node(&root, 25);
    insert_node(&root, 4);
    insert_node(&root, 6);
    insert_node(&root, 1);
    insert_node(&root, 2);
    insert_node(&root, 45);

    print_tree_depth(root);

    printf("Length: %d\n", length(root));

    sum_tree(root, &sum);

    printf("Sum: %d\n", sum);

    max_tree(root, &max);

    printf("Max: %d\n", max);

    root_copy = copy_tree(root);

    printf("Tree copy: \n");

    print_tree_depth(root_copy);

    node_t *tree3 = create_node(111);

    if (check_identical_tree(root, root_copy))
        printf("Trees are identical.\n");
    else
        printf("Trees are not equal.\n");

    free_tree(root);

    free_tree(root_copy);

    free_tree(tree3);

    return 0;
}
