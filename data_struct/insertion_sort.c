/*
 * Although insertion sort is an O(n2) algorithm, its simplicity, low overhead,
 * good locality of reference and efficiency make it a good choice in two cases: 
 *	(i) small n, 
 *	(ii) as the final finishing-off algorithm for O(n logn) algorithms 
 *  such as mergesort and quicksort.
 *
 */
#include <stdio.h>

print_array(int *elements, int size, char *info)
{
	int iter = 0;
	printf("%s : ", info);
	for(iter = 0; iter < size; iter++) {
		printf("%d ", elements[iter]);
	}
	printf("\n");
}

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp; 
}

/*
 * insetion_sort: for n swap the i'th element to the left 
 */
int insertion_sort(int *elements, int size)
{
	int iter = 0;
	int next = 0;

	for(iter = 0; iter < size -2 ; iter ++) {
		next = iter + 1;
		while(next) {
			if(elements[next] < elements[next-1]) {
				swap(&elements[next], &elements[next-1]);
				next--;
			} else {
				/* no need to swap anymore*/
				break;
			}
		}

	}
}

int main(int argc, char const *argv[])
{	
	int test1[7] = {4, 5, 1, 8, 9, 0, 1};
	int test2[8] = {1, 1, 1, 2, 2, 0, 1, 15};
	int test3[7] = {4, 0, -1, -8, -9, 0, 1};
			
	print_array(test1, 7, "Before");
	insertion_sort(test1, 7);
	print_array(test1, 7, "After");

	print_array(test2, 8, "Before");
	insertion_sort(test2, 8);
	print_array(test2, 8, "After");

	print_array(test3, 7, "Before");
	insertion_sort(test3, 7);
	print_array(test3, 7, "After");

	return 0;
}