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
