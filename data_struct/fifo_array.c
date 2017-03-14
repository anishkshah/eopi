#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FIFO_SIZE 100

/*
	   ---------------
TAIL   --> --> --> -->	HEAD
	   ---------------
*/

struct fifo {
	int 	*data;
	int 	head;
	int 	tail;
};

struct fifo* queue_init(int size)
{
	struct fifo *queue = NULL;	
	queue = calloc(1, sizeof(struct fifo));
	if(queue)
	{
		queue->data = calloc(size, sizeof(int));
	}
	return queue;
}

void put_queue(struct fifo* queue, int data)
{
	if(queue == NULL)
	{
		return;
	}

	if(queue->tail == queue->head)
	{
		queue->tail = 0;
		queue->head	= 0;
	}

	if(queue->tail == FIFO_SIZE)
	{
		printf("Queue Full\n");
	}

	queue->data[queue->tail] = data;
	queue->tail++;

	return;
}

int get_queue(struct fifo* queue)
{
	int data = -1;

	if(queue == NULL)
	{
		return data;
	}

	data = queue->data[queue->head];
	queue->head++;
	return data;
}

int main()
{
	struct fifo *data_queue = NULL;
	int count = 50;
	int value = 0;
	data_queue = queue_init(FIFO_SIZE);
	if(data_queue == NULL)
	{
		perror("ENOMEM\n");
		exit(1);
	}

	while(count)
	{
		put_queue(data_queue, count);
		count--;
	}

	count = 50;
	while(count)
	{
		value = get_queue(data_queue);
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
}