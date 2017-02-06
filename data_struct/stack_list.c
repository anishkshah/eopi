#include <stdio.h>
#include <string.h>
#include <errno.h>

struct node_stack {
    int     data;
    struct node_stack *next;
};

struct node_stack *stack_node_init(int data)
{
    struct node_stack *new = NULL:
    new = malloc(sizeof(node_stack));
    if(new) {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

/* Add to new node to the head of the list */
int stack_push(struct stack_node **root, int data)
{
    int error = 0;
    struct stack_node *new = NULL;

    new = stack_node_init(data);
    if(new) {
        new->next = *root;
        *root = new;
        error = 0;
    } else {
        error = ENOMEM;
    }

    return error;
}

/* Return the new value form head */
int stack_pop(struct stack_node *root)
{
    struct stack_node * temp = NULL;
    int value = 0;
    if(root == NULL)
        return 0;
    temp = root->next;
    value = root->value;
    free(root);
    return value;
}

int main ()
{
    struct stack_node root;

    stack_push(&root, 5);
    stack_push(&root, 8);
    stack_push(&root, -5);

    printf("stack top %d\n", stack_pop(root));

    return 0;
}