#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct node_stack {
    int     data;
    int     min;
    struct node_stack *next;
};

struct node_stack *stack_node_init(int data)
{
    struct node_stack *new = NULL;
    new = calloc(1, sizeof(struct node_stack));
    if(new) {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

struct node_stack *stack_init(int data)
{
    struct node_stack *new = NULL;
    new = calloc(1, sizeof(struct node_stack));
    if(new) {
        new->data = data;
        new->min = data;
        new->next = NULL;
    }
    return new;
}

/* Add to new node to the head of the list */
int stack_push(struct node_stack **root, int data)
{
    int error = 0;
    struct node_stack *new = NULL;

    if(*root == NULL) {
        printf("Stack uninitalized\n");
        return -1;
    }

    new = stack_node_init(data);
    if(new) {

        // Keep track of min
        if(*root == NULL) {
            new->min = data;
        } else {
            if((*root)->min < data) {
                new->min = (*root)->min;
            } else {
                new->min = data;
            }
        }

        new->next = *root;
        *root = new;
    } else {
        error = ENOMEM;
    }

    return error;
}

/* Return the new value form head */
int stack_pop(struct node_stack **root)
{
    struct node_stack *temp = NULL;
    int value = 0;

    /*Empty List*/
    if(*root == NULL)
        return 0;
    
    temp = *root;
    value = temp->data;
    *root = (*root)->next;
    free(temp);
    return value;
}

/* Get min form the stack */
int stack_min(struct node_stack *head)
{
    if(head == NULL) {
        return 0;
    }
    return head->min;
}

int main ()
{
    struct node_stack *head = NULL;

    head = stack_init(5);

    stack_push(&head, 5);
    stack_push(&head, 8);
    stack_push(&head, -5);
    stack_push(&head, 10);
    stack_push(&head, 15);

    printf("stack min %d\n", stack_min(head));

    printf("stack pop %d \n", stack_pop(&head));
    printf("stack pop %d \n", stack_pop(&head));
    printf("stack pop %d \n", stack_pop(&head));

    printf("stack min %d\n", stack_min(head));

    return 0;
}