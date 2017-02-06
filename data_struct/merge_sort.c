/*
 * The merge sort is a recursive sort of order n*log(n).
 * It is notable for having a worst case and average complexity of O(n*log(n)),   
 * and a best case complexity of O(n) (for pre-sorted input).
 * The basic idea is to split the collection into smaller groups by halving it 
 * until the groups only have one element or no elements (which are both entirely sorted groups).
 * Then merge the groups back together so that their elements are in order.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void print_array(int *elements, int size, char *info)
{
	int i = 0;
	printf("%s : ", info);
	for(i = 0; i < size; i++) {
		printf("%d ", elements[i]);
	}
	printf("\n");
	return;
}

void verify_sort(int * elements, int low , int high)
{
	int i = 0;
	for(i = low; i < high; i++) {
		if(elements[i] > elements[i+1]) {
			assert(0);
		}
	}
}

/*
 * 	merges a partailly sorted array 
 * 	
 *  low    	  mid mid+1       high
 *  1 3 5 8 9 12   4 7 7 8 12 13
 *
 *  low to mid is sorted and mid+1 to hight is sorted
 */

void merge_array(int *elements, int *aux_elements, int low, int mid, int high)
{
	int i = 0;
	int l1 = low;
	int l2 = mid+1;

	// copy data in auxillary array
	for(i = low ; i<=high ; i++){
		aux_elements[i] = elements[i];
	}

	for(i = low; i <= high; i++) {

		/* completed the low to mid array */
		if(l1 > mid) {	
			elements[i] = aux_elements[l2++];
		} 
		/* completed the mid+1 to high array*/
		else if(l2 > high) {
			elements[i] = aux_elements[l1++];	
		} 
		/* the elem[low] < elem[mid+1]*/
		else if(aux_elements[l1] < aux_elements[l2]) {
			elements[i] = aux_elements[l1++];
		}  else {
			elements[i] = aux_elements[l2++];
		}
	}
}

void sort(int *elements, int *aux_elements, int low, int high)
{	
	int mid = low + (high - low) /2 ;
	if(low >= high) return;

	sort(elements, aux_elements, low, mid);
	sort(elements, aux_elements, mid+1, high);
	merge_array(elements, aux_elements, low, mid, high);
}

int main()
{
	int test1[7] = {4, 5, 1, 8, 9, 0, 1};
	int test2[7] = {1, 1, 1, 2, 2, 0, 1};
	int test3[7] = {4, 0, -1, -8, -9, 0, 1};

	int *test1_aux = malloc(sizeof(test1));
	int *test2_aux = malloc(sizeof(test2));
	int *test3_aux = malloc(sizeof(test3));

	print_array(test1, 7, "Before");
	sort(test1, test1_aux, 0, 6);
	print_array(test1, 7, "After");

	print_array(test2, 7, "Before");
	sort(test2, test2_aux, 0, 6);
	print_array(test2, 7, "After");

	print_array(test3, 7, "Before");
	sort(test3, test3_aux, 0, 6);
	print_array(test3, 7, "After");

	free(test1_aux);
	free(test2_aux);
	free(test3_aux);
	return 0;
}