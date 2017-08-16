<<<<<<< ce855e14a9c8e76c0190ac7f5c9ff978816c87fc
struct QueueNode {
    int key;
    int value;
    struct QueueNode* prev;
    struct QueueNode* next;
};
struct Queue {
    int capacity;
    int count;
    struct QueueNode* front;
    struct QueueNode* rear;
};
struct Hash {
    int size;
    struct QueueNode** array;
};
struct Queue* queue;
struct Hash* hash;
struct Queue* createQueue(int c) {
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
    q->capacity = c;
    q->count = 0;
    q->front=q->rear=NULL;
    return q;
}
struct Hash* createHash(int s) {
    struct Hash* h= (struct Hash*) malloc(sizeof(struct Hash));
    h->size = s;
    h->array = (struct QueueNode**) malloc(s*sizeof(struct QueueNode*));
    int i;
    for(i=0;i<s;i++) {
        h->array[i] = NULL;
    }
    return h;
}
struct QueueNode* newNode(int key,int value) {
    struct QueueNode* node = (struct QueueNode*) malloc(sizeof(struct QueueNode));
    node->key = key;
    node->value = value;
    node->prev=NULL;
    node->next = NULL;
    return node;
}
int isEmpty(struct Queue* q) {
    return q->rear == NULL;
}
int isFull(struct Queue* q) {
    return q->count == q->capacity;
}
void deQueue(struct Queue* q) {
    if(isEmpty(q)) {
        return;
    }
    struct QueueNode* temp = q->rear;
    if(q->front== q->rear) {
        q->front=NULL;
    }
    if(temp->prev) {
        temp->prev->next = NULL;
    }
    q->rear = q->rear->prev;
    
    q->count--;
    free(temp);
}
void enqueue(struct Queue* q,int key, int value) {
    if(isFull(queue)) {
        hash->array[q->rear->key] = NULL;
        deQueue(q);
    } 
    struct QueueNode* node = newNode(key,value);
    if(isEmpty(queue)) {
        q->front=q->rear = node;
    } else {
        node->next = q->front;
        q->front->prev = node;
        q->front = node;
    }
    hash->array[key] = node;
    q->count++;
}


void init(int capacity) {
if(queue != NULL) {
    free(queue);
}
if(hash!= NULL) {
    free(hash);
}
queue = createQueue(capacity);
hash = createHash(1000);
}

void moveNodeToFront(struct QueueNode* node, struct Queue* q) {
            node->prev->next = node->next;
            if(node->next) {
                node->next->prev = node->prev;
            }
            if(node==queue->rear) {
                queue->rear = node->prev;
            }
            node->next = queue->front;
            queue->front->prev = node;
            node->prev = NULL;
            queue->front = node;
}

int get(int key) {
    struct QueueNode* node = hash->array[key];
    if(node != NULL) {
        int val = node->value;
        if(node != queue->front) {
           moveNodeToFront(node,queue);
        }
        return val;
    }else {
        return -1;
    }
}

void set(int key, int value) {
    struct QueueNode* node = hash->array[key];
    if(node == NULL) {
       enqueue(queue,key,value); 
    } else {
        node->value = value;
        if(node != queue->front) {
            moveNodeToFront(node,queue);
        }
    }
}
=======
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
>>>>>>> lru cache partail
