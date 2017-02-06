#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/*
 * The pq[0] is the number of elements in the heap.
 */
int pq[MAX+1];

int N = 0; // Number of elements in the PQ 

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = *b;
}

/* Move the value at index k to satisfy the heap property */
void swim(int k)
{
	while(k > 1 && (pq[k/2] < pq[k])) {
		swap(pq[k/2], pq[k]);
		k = k/2;
	}
}

/* Move the parent to the correct position when it is smaller than the child.
 * 
 */
void sink(int k)
{
	int small_child = 0;

	while(2k < N ) {

		if(pq[2k] < pq[2k+1]) {
			small_child = 2k ;
		} else {
			small_child = 2k+1;
		}

		/* Heap property satisfied so stop */
		if(! pq[k] < pq[small_child]) {
			break;
		}
		swap(pq[k], pq[small_child]);
		k = 2k;
	}
}

/* Put the value in the last position of the array PQ and perform SWIM */
int insert(int value)
{
	if(N < MAX) {
		pq[++N] = value;
		swim(N);
		return 0;
	}
	return -1;
}

/* return the MAX of the heap and remove it form the heap structure.
 * Swap the last element with the maximum element. Decrement N count.
 * Do sink at the pq[1].
 */
int delete_max()
{
	int max = pq[1];
	swap(pq[1], pq[N]);
	N--;
	pq[N+1] = 0;
	sink(1);
	return max;
}


int main(int argc, char const *argv[])
{
	memset(pq, 0, sizeof(pq));
	N = 0;
	return 0;
}