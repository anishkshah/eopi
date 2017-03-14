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

void put_fif0(struct fifo *queue, int node)
{
    struct fifo_node *new = NULL;

    if(queue == NULL) {
        return;
    }

    new = calloc(1, sizeof(struct fifo_node));
    new->data = node;
    
    if(queue->head == NULL)
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
    int data = 0;

    if(queue == NULL) return -1;

    if(queue->head == NULL)
    {
        queue->head == NULL;
        queue->tail == NULL;
        return -1;
    }
    else
    {
        data = queue->head->data;
        curr_head = queue->head;
        queue->head = queue->head->next;
    }
    
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
    int count = 50;
    int value = 0;

    queue = fifo_init();

    while(count)
    {
        put_fif0(queue, count);
        count--;
    }

    count = 50;
    while(count)
    {
        value = get_fif0(queue);
        printf("%d : ", value);
        if(value != count)
        {
            printf("error\n");
            assert(0);
        }
        count--;
    }
    printf("\n");
    return 0;
    return 0;
}