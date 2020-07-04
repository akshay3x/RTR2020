#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//variable declarations
	int *ptr_to_int_array = NULL;
	unsigned int int_array_length = 0;
	int ac_i;

	//code
	printf("\n\n");
	printf("Enter number of elements for integer array: ");
	scanf("%d", &int_array_length);

	//memory allocation
	ptr_to_int_array = (int *) malloc(sizeof(int) * int_array_length);

	//validating allocation
	if(ptr_to_int_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed: Exiting...\n");
		return (0);
	}

	else
	{
		printf("\n\n");
		printf("Addresses Allocated: %p to %p", ptr_to_int_array, ptr_to_int_array + (int_array_length - 1));
	}

	//assigning input values
	printf("\n\n");
	printf("Enter %d numbers for the integer Array:\n", int_array_length);
	for(ac_i = 0; ac_i < int_array_length; ac_i++)
	{
		printf(" number %d : ", ac_i + 1);
		scanf("%d", (ptr_to_int_array + ac_i));
	}

	//displaying values with array indexing
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < int_array_length; ac_i++)
		printf(" ptr_to_int_array[%d] = %d\t At Addresses &ptr_to_int_array[%d] : %p\n", ac_i, ptr_to_int_array[ac_i], ac_i, &ptr_to_int_array[ac_i]);

	//displaying values with pointers
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < int_array_length; ac_i++)
		printf(" *(ptr_to_int_array + %d) = %d\t Address (ptr_to_int_array + %d) : %p\n", ac_i, *(ptr_to_int_array + ac_i), ac_i, (ptr_to_int_array + ac_i));

	//freeing memory
	if(ptr_to_int_array)
	{
		free(ptr_to_int_array);
		ptr_to_int_array = NULL;
		printf("\n\n");
		printf("Memory freed: ptr_to_int_array\n");
	}

	return (0);
}
