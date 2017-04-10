#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct fifo_node{
    int data;
    struct fifo_node *next;
};

struct fifo{
    struct fifo_node *head;
    struct fifo_node *tail;
};

int queue_empty(struct fifo *queue)
{

    if(!queue) return -1;

    if(queue && (queue->head == NULL && queue->tail == NULL))
    {
        return 1;
    }

    return 0;
}

void put_fif0(struct fifo *queue, int node)
{
    struct fifo_node *new = NULL;

    if(queue == NULL)
    {
        return;
    }

    new = calloc(1, sizeof(struct fifo_node));
    new->data = node;
    
    if(queue_empty(queue))
    {
        queue->head = new;
        queue->tail = new;
        return;
    }
    
    queue->tail->next = new; 
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
    
    if(reset) queue->tail = NULL;

    free(curr_head);
    return data;
}

struct fifo *fifo_init()
{
    struct fifo *queue = NULL;
    queue = calloc(1, sizeof(struct fifo));
    return queue;
}

int main()
{
    struct fifo * queue = NULL;
    int count = 100;
    int read_count = 0;
    int value = 0;

    queue = fifo_init();

    while(count || (queue_empty(queue) == 0))
    {
        value = rand()%50;
        if(value%2)
        {
            printf("put_fif0 %d\n", value);
            put_fif0(queue, value);
        }
        else
        {
            value =  get_fif0(queue);
            printf("get_fif0 %d\n", value);
            read_count ++;
        }
    }

    printf("read_count:  %d\n", read_count);
    return 0;
}