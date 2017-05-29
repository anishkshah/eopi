#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
//#include "helper.h"

struct fifo_node{
    int data;
    struct fifo_node *next;
};

struct fifo{
    struct fifo_node *head;
    struct fifo_node *tail;
};

struct stack_node{
    int data;
    struct stack_node *next;
};

int push_stack(struct stack_node **stack, int data)
{
	struct stack_node *temp = NULL;

	temp = calloc(1, sizeof(struct stack_node));
	if(temp == NULL) return -1;	

	temp->data = data;

	if(*stack == NULL)
	{
		*stack = temp;
		return 0;
	}

	temp->next = *stack;
	*stack = temp;
	return 0;
}

int pop_stack(struct stack_node **stack , int *data)
{
	struct stack_node *temp = NULL;
	
	if(*stack == NULL) return -1;

	temp = *stack;
	*data = temp->data;
	*stack = (*stack)->next;
	free(temp);
	return 0;
}

void stack_print(struct stack_node **stack)
{
    int data = 0;
    int ret = 0;

    while(ret == 0)
    {
        ret = pop_stack(stack, &data);
        if(ret == 0) printf("%d -- ", data);
    }
    printf("\n");
    return;
}

struct fifo *fifo_init()
{
    struct fifo *queue = NULL;
    queue = calloc(1, sizeof(struct fifo));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

int queue_empty(struct fifo *queue)
{

    if(!queue) return -1;

    if(queue && (queue->head == NULL && queue->tail == NULL))
    {
        return 1;
    }

    return 0;
}

void put_fif0(struct fifo *queue, int data)
{
    struct fifo_node *new_fifo = NULL;

    if(queue == NULL) {
        return;
    }

    new_fifo = calloc(1, sizeof(struct fifo_node));
    new_fifo->data = data;
    
    if(queue_empty(queue))
    {
        queue->head = new_fifo;
        queue->tail = new_fifo;
        return;
    }
    
    queue->tail->next = new_fifo; 
    queue->tail = queue->tail->next;
    return;
}

int get_fif0(struct fifo *queue)
{
    struct fifo_node *new_head = NULL;
    struct fifo_node *curr_head = NULL;
    int reset = 0;
    int data = 0;

    if(queue_empty(queue)) return -1;

    if(queue->head == queue->tail)
    {
        reset = 1;
    }

    data = queue->head->data;
    curr_head = queue->head;
    queue->head = queue->head->next;
    
    if(reset)
    {	
    	queue->tail = NULL;
    	queue->head = NULL;
    }
    //free(curr_head);
    return data;
}
