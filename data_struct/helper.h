#ifndef HELPER_H
#define HELPER_H

struct fifo_node{
    int data;
    struct fifo_node *next;
};

struct fifo{
    struct fifo_node *head;
    struct fifo_node *tail;
};

struct fifo *fifo_init();

int queue_empty(struct fifo *queue);

void put_fif0(struct fifo *queue, int data);

int get_fif0(struct fifo *queue);

#endif