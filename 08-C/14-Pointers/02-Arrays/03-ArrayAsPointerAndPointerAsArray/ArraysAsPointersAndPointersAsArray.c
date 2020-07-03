#include <stdio.h>

int main(void)
{
	//variable declarations
	int int_array[] = {20, 21, 22, 23, 34, 25, 26, 27, 28, 29};
	int *ptr_to_array = NULL;
	
	//code
	printf("\n\n");
	printf("--- Displaying values using array name as pointer access ---\n");
	printf(" *(int_array + 0) = %d,   is at addrees (int_array + 0) = %p\n", *(int_array + 0), (int_array + 0));
	printf(" *(int_array + 1) = %d,   is at addrees (int_array + 1) = %p\n", *(int_array + 1), (int_array + 1));
	printf(" *(int_array + 2) = %d,   is at addrees (int_array + 2) = %p\n", *(int_array + 2), (int_array + 2));
	printf(" *(int_array + 3) = %d,   is at addrees (int_array + 3) = %p\n", *(int_array + 3), (int_array + 3));
	printf(" *(int_array + 4) = %d,   is at addrees (int_array + 4) = %p\n", *(int_array + 4), (int_array + 4));
	printf(" *(int_array + 5) = %d,   is at addrees (int_array + 5) = %p\n", *(int_array + 5), (int_array + 5));
	printf(" *(int_array + 6) = %d,   is at addrees (int_array + 6) = %p\n", *(int_array + 6), (int_array + 6));
	printf(" *(int_array + 7) = %d,   is at addrees (int_array + 7) = %p\n", *(int_array + 7), (int_array + 7));
	printf(" *(int_array + 8) = %d,   is at addrees (int_array + 8) = %p\n", *(int_array + 8), (int_array + 8));
	printf(" *(int_array + 9) = %d,   is at addrees (int_array + 9) = %p\n", *(int_array + 9), (int_array + 9));
	
	//
	ptr_to_array = int_array;
	printf("\n\n");
	printf("--- Displaying values using pointer variable as array indexing ---\n");
	printf(" ptr_to_array[0] = %d,   is at addrees &ptr_to_array[0] = %p\n", ptr_to_array[0], &ptr_to_array[0]);
	printf(" ptr_to_array[1] = %d,   is at addrees &ptr_to_array[1] = %p\n", ptr_to_array[1], &ptr_to_array[1]);
	printf(" ptr_to_array[2] = %d,   is at addrees &ptr_to_array[2] = %p\n", ptr_to_array[2], &ptr_to_array[2]);
	printf(" ptr_to_array[3] = %d,   is at addrees &ptr_to_array[3] = %p\n", ptr_to_array[3], &ptr_to_array[3]);
	printf(" ptr_to_array[4] = %d,   is at addrees &ptr_to_array[4] = %p\n", ptr_to_array[4], &ptr_to_array[4]);
	printf(" ptr_to_array[5] = %d,   is at addrees &ptr_to_array[5] = %p\n", ptr_to_array[5], &ptr_to_array[5]);
	printf(" ptr_to_array[6] = %d,   is at addrees &ptr_to_array[6] = %p\n", ptr_to_array[6], &ptr_to_array[6]);
	printf(" ptr_to_array[7] = %d,   is at addrees &ptr_to_array[7] = %p\n", ptr_to_array[7], &ptr_to_array[7]);
	printf(" ptr_to_array[8] = %d,   is at addrees &ptr_to_array[8] = %p\n", ptr_to_array[8], &ptr_to_array[8]);
	printf(" ptr_to_array[9] = %d,   is at addrees &ptr_to_array[9] = %p\n", ptr_to_array[9], &ptr_to_array[9]);

	return(0);
}
