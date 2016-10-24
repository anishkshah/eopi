#include <stdio.h>
#include <string.h>

#define STACK_MAX 100

struct stack {
    int     data[STACK_MAX];
    int     size;
};


void stack_init(struct stack *S)
{
    S->size = 0;
    memset(S->data, 0, sizeof(int) * STACK_MAX);
}

int stack_top(struct stack *S)
{
    if (S->size == 0) {
        fprintf(stderr, "Error: stack empty\n");
        return -1;
    } 

    return S->data[S->size-1];
}

/* Post incremnt the size to next location in array*/
void stack_push(struct stack *S, int data)
{
    if (S->size < STACK_MAX)
        S->data[S->size++] = data;
    else
        fprintf(stderr, "Error: stack full\n");
}

/* The size points to the next location before the current top */
void stack_pop(struct stack *S)
{
    if (S->size == 0)
        fprintf(stderr, "Error: stack empty\n");
    else
        S->size--;
}

int main ()
{
    struct stack S;

    stack_init(&S);


    stack_push(&S, 5);
    stack_push(&S, 8);

    printf("stack top %d\n", stack_top(&S));

    return 0;
}