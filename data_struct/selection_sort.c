/*
 * Its primary purpose is for when writing data is very expensive (slow) when compared to reading, 
 * eg. writing to flash memory or EEPROM. No other sorting algorithm has less data movement.
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
 * get_min_index:  gets min index of an array starting from curr
 */

int get_min_index(int *elements, int curr, int size)
{
	int iter = curr + 1;
	int min = elements[curr];
	int min_ptr = curr;
	for(iter; iter < size ; iter++){
		if(min > elements[iter]) {
			min = elements[iter];
			min_ptr = iter;
		}
	}
	return min_ptr;
}

/*
 * selection_sort: sorts the elements by swapping a[i] with a[min] to the array on left of a[i]
 * 				   time: O(n2)
 * 				   space: O(n)
 */

void selection_sort(int *elements, int size)
{
	int curr = 0;
	int min_elem_index = 0;

	for(curr = 0; curr < size-1; curr++) {
		min_elem_index = get_min_index(elements, curr, size);
		if(curr !=  min_elem_index) {
			swap(&elements[curr], &elements[min_elem_index]);
		}
	}
}



int main()
{
	int test1[7] = {4, 5, 1, 8, 9, 0, 1};
	int test2[7] = {1, 1, 1, 2, 2, 0, 1};
	int test3[7] = {4, 0, -1, -8, -9, 0, 1};
			
	print_array(test1, 7, "Before");
	selection_sort(test1, 7);
	print_array(test1, 7, "After");

	print_array(test2, 7, "Before");
	selection_sort(test2, 7);
	print_array(test2, 7, "After");

	print_array(test3, 7, "Before");
	selection_sort(test3, 7);
	print_array(test3, 7, "After");

	return 0;
}