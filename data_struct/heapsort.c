#include <stdio.h>
#include <stdlib.h>

#define LCHILD(X) 2*X
#define RCHILD(X) 2*X + 1
#define PARENT(X) (X/2)

struct binary_heap {
    int size ;
    int *elements ;
}

struct binary_heap init_heap(int size)
{
    struct binary_heap *hp = NULL;

    hp = malloc(sizeof(struct binary_heap));
    if(hp == NULL) return NULL;
    hp->size = size;
    hp->elements = malloc(size * (sizeof(int)));
    memset(hp->elements, 0, size * (sizeof(int)));
    return hp ;
}

void swap(struct binary_heap *hp, int pos_x, int psx_y)
{
    int temp = hp->elements[x];
    hp->elements[x] = hp->elements[y] ;
    hp->elements[y] = temp;
}

/*
 *  heapify_sink_down : To fix the heap property at given position k for binary_heap hp 
 *
 *
 */
void heapify_sink_down(struct binary_heap *hp, int k)
{
    if(hp == NULL) return;

    while(k > 1 && (hp->elements[k/2] < hp->elements[k])) {
        swap(hp, k/2, k);
        k = k/2;
    }

    return;
}


/*
 *  heapify_swim_up : To fix the heap property at given position k for binary_heap hp
 *
 *
 */
void heapify_swim_up(struct binary_heap *hp, int k)
{
    if(hp == NULL) return;

    while(k > 1 && (hp->elements[k/2] < hp->elements[k])) {
        swap(hp, k/2, k);
        k = k/2;
    }

    return;
}

void insert_node(struct binary_heap *hp, int value)
{
    if(hp == NULL) return NULL;

    /* elements[0] has the current position */
    if(hp->size > hp->elements[0]) {
        hp->elements[0]++;
        hp->elements[hp->elements[0]] = value;
        heapify_swim_up(hp, hp->elements[0]);
    }
}


void deleteNode(minHeap *hp) {
    if(hp->size) {
        printf("Deleting node %d\n\n", hp->elem[0].data) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("\nMin Heap is empty!\n") ;
        free(hp->elem) ;
    }
}

void buildMinHeap(minHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.data = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}

void inorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}

void preorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        preorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        preorderTraversal(hp, RCHILD(i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
}

void postorderTraversal(minHeap *hp, int i) {
    printf("%d ", hp->elem[i].data) ;
    if(LCHILD(i) < hp->size) {
        postOrderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        postorderTraversal(hp, RCHILD(i)) ;
    }
}

void levelOrderTraversal(minHeap *hp) {
    int i ;
    for(i = 0; i < hp->size; i++) {
        printf("%d ", hp->elem[i].data) ;
    }
}