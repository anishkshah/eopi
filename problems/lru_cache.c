#include <stdio.h>
#include <string.h>

#define MAP_SIZE 1024*1024

struct node
{
	int key;
	int value;
	struct node *next;
	struct node *prev;
}

struct lru_list
{
	struct node *head;
	struct node *tail;
	int size;
}

struct lru_cache
{
	int max_size;
	int size;

	struct node **arr;
	struct list *queue;
}

struct lru_cache *init_cache(int size)
{
	struct lru_cache *temp = NULL;
	temp = calloc(1, sizeof(struct lru_cache));
	temp->size = size;

	temp->arr = calloc(MAP_SIZE, sizeof(struct node *));
	temp->queue = calloc(1, sizeof(struct lru_list *));
	return temp;
}

struct node *new_node(int key, int value)
{
	struct node *temp = calloc(1, sizeof(struct node));
	temp->key = key;
	temp->value = value;
}

void node_delete(struct lru_list *queue, struct node *curr, bool do_delete)
{

	if(!queue) return;

	if(queue->head == curr)
	{
		if(queue->head->next)
		{
			queue->head->next->prev = NULL;
		}
		queue->head = queue->head->next;
	}	
	else if(queue->tail == curr)
	{
		queue->tail = queue->tail->prev;
		queue->tail->next = NULL;	
	}
	else
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}

	curr->next = NULL;
	curr->prev = NULL;
	if(do_delete)
	{
		free(curr);
	}
}

void node_add_head(struct lru_list *queue, struct node *in)
{
	if(!queue) return;

	in->next = queue->head;
	queue->head->prev = in;
	queue->head = in;
}


void node_add_tail(struct lru_list *queue, struct node *in)
{
	if(!queue) return;

	queue->tail->next = in;
	in->prev = queue->tail;
	queue->tail = in;
	return;
}

void put_cache(struct lru_cache *cache, int key, int value)
{
	struct node *curr = cache->arr[key];
	struct node *temp = NULL;
	int del_key = -1;

	if(curr)
	{
		node_delete(cache->queue, curr, 0);
		node_add_tail(cache->queue, curr);
	}

	if(cache->size == cache->max_size)
	{
		temp = cache->queue->head;
		del_key = temp->key;
		cache->arr[del_key] = NULL;
		node_delete(cache->queue, temp, 1);
		temp = NULL;
		temp = new_node(key, value);
		node_add_tail(cache->queue, temp);
		cache->arr[key] = temp;
	}
	else
	{
		temp = new_node(key, value);
		node_add_tail(cache->queue, temp);
		cache->arr[key] = temp;
	}

	return;
}

int get_cache(struct lru_cache *cache, int key)
{
	struct node *curr = cache->arr[key];

	if(!curr)
	{	
		return -1;
	}

	node_delete(cache->queue, temp, 0);
	node_add_tail(cache->queue, temp);

	return curr->value;
}