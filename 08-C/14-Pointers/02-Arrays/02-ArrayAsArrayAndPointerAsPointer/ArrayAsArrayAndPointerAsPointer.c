#include <stdio.h>

int main(void)
{
	//varable declarations
	int int_array[] = {19, 18, 17, 16, 15, 14, 13, 12, 11, 10};
	int *ptr_to_array = NULL;

	//displaying values using array name as base address
	printf("\n\n");
	printf("--- Values Using Array Indices ---\n");
	printf(" int_array[0] = %d,   is at address = %p\n", int_array[0], &int_array[0]);
	printf(" int_array[1] = %d,   is at address = %p\n", int_array[1], &int_array[1]);
	printf(" int_array[2] = %d,   is at address = %p\n", int_array[2], &int_array[2]);
	printf(" int_array[3] = %d,   is at address = %p\n", int_array[3], &int_array[3]);
	printf(" int_array[4] = %d,   is at address = %p\n", int_array[4], &int_array[4]);
	printf(" int_array[5] = %d,   is at address = %p\n", int_array[5], &int_array[5]);
	printf(" int_array[6] = %d,   is at address = %p\n", int_array[6], &int_array[6]);
	printf(" int_array[7] = %d,   is at address = %p\n", int_array[7], &int_array[7]);
	printf(" int_array[8] = %d,   is at address = %p\n", int_array[8], &int_array[8]);
	printf(" int_array[9] = %d,   is at address = %p\n", int_array[9], &int_array[9]);

	ptr_to_array = int_array;
	//displaying using pointer assigned to base address
	printf("\n\n");
	printf("--- Values Using Pointer ---\n");
	printf(" *(ptr_to_array + 0) = %d,   is at address (ptr_to_array + 0) = %p\n", *(ptr_to_array + 0), (ptr_to_array + 0));
	printf(" *(ptr_to_array + 1) = %d,   is at address (ptr_to_array + 1) = %p\n", *(ptr_to_array + 1), (ptr_to_array + 1));
	printf(" *(ptr_to_array + 2) = %d,   is at address (ptr_to_array + 2) = %p\n", *(ptr_to_array + 2), (ptr_to_array + 2));
	printf(" *(ptr_to_array + 3) = %d,   is at address (ptr_to_array + 3) = %p\n", *(ptr_to_array + 3), (ptr_to_array + 3));
	printf(" *(ptr_to_array + 4) = %d,   is at address (ptr_to_array + 4) = %p\n", *(ptr_to_array + 4), (ptr_to_array + 4));
	printf(" *(ptr_to_array + 5) = %d,   is at address (ptr_to_array + 5) = %p\n", *(ptr_to_array + 5), (ptr_to_array + 5));
	printf(" *(ptr_to_array + 6) = %d,   is at address (ptr_to_array + 6) = %p\n", *(ptr_to_array + 6), (ptr_to_array + 6));
	printf(" *(ptr_to_array + 7) = %d,   is at address (ptr_to_array + 7) = %p\n", *(ptr_to_array + 7), (ptr_to_array + 7));
	printf(" *(ptr_to_array + 8) = %d,   is at address (ptr_to_array + 8) = %p\n", *(ptr_to_array + 8), (ptr_to_array + 8));
	printf(" *(ptr_to_array + 9) = %d,   is at address (ptr_to_array + 9) = %p\n", *(ptr_to_array + 9), (ptr_to_array + 9));

	return (0);
}

