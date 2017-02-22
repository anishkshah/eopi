#include <stdio.h>
#include <stdlib.h>



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

void swap(struct binary_heap *hp, int pos_x, int pos_y)
{
    int temp = hp->elements[pos_x];
    hp->elements[pos_x] = hp->elements[pos_y] ;
    hp->elements[pos_y] = temp;
}

/*
 *  heapify_sink_down : To fix the heap property at given position k for binary_heap hp 
 */
void heapify_sink_down(struct binary_heap *hp, int k)
{
    int child_l = 0;
    int child_r = 0;
    int smallest = 0;
    if(hp == NULL) return;

    while(2k < hp->elements[0]) {
        child_l = 2k;
        child_r = 2k +1;
        smallest = k;
        if((child_l < hp->elements[0]) && hp->elements[child_l] < hp->elements[smallest]) {
            smallest = child_l;
        }
        if((child_r < hp->elements[0]) && hp->elements[child_r] < hp->elements[smallest]) {
            smallest = child_l;
        }

        if(smallest == k) break; //heapifying done
        else swap(hp, k, smallest);

        k = child_l;
    }
    return;
}

/*
 *  heapify_swim_up : The element at pos K sips up the tree to fix the heapifying property.
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
    if(hp == NULL) return;

    /* elements[0] has the current position */
    if(hp->size > hp->elements[0]) {
        hp->elements[0]++;

        /* inset the new elemet in the end and swim up */
        hp->elements[hp->elements[0]] = value;
        heapify_swim_up(hp, hp->elements[0]);
    }
}

/*
 *  Delete_max - swap the last element to the root and swim_down
 */
void delete_max(struct binary_heap *hp)
{
    if(hp == NULL) return;

    if(hp->size > 1) {
        /* swap last elem to head */
        swap(hp, hp->elements[1], hp->elements[hp->elements[0]]);
        /* reset last elem*/
        hp->elements[hp->elements[0]] = 0;
        hp->elements[0]--;
        heapify_sink_down(hp, 1);
    } else {
        /* Just the head or empty heap */
        hp->elements[1] = 0;
        hp->elements[0] = 0;
    }
    return;
}

void inorder_traversal(minHeap *hp, int i) {
    if((2i) < hp->size) {
        inorder_traversal(hp, (2i)) ;
    }
    printf("%d ", hp->elem[i].data) ;
    if((2i+1) < hp->size) {
        inorder_traversal(hp, (2i+1)) ;
    }
}

void preorder_traversal(minHeap *hp, int i) {
    if((2i) < hp->size) {
        preorder_traversal(hp, (2i)) ;
    }
    if((2i+1) < hp->size) {
        preorder_traversal(hp, (2i+1)) ;
    }
    printf("%d ", hp->elem[i].data) ;
}

void postorder_traversal(minHeap *hp, int i) {
    printf("%d ", hp->elem[i].data) ;
    if((2i) < hp->size) {
        postorder_traversal(hp, (2i)) ;
    }
    if((2i+1) < hp->size) {
        postorder_traversal(hp, (2i+1)) ;
    }
}

/* BFS*/
void levelorder_traversal(minHeap *hp) {
    int i ;
    for(i = 0; i < hp->size; i++) {
        printf("%d ", hp->elem[i].data) ;
    }
}