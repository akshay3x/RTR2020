#include <stdio.h>

int main(void)
{
	//varaible declarations
	int int_array[10];
	int *ptr_to_array;
	int ac_i;

	//code
	//Assigning Values
	for(ac_i = 0; ac_i < 10; ac_i ++)
		int_array[ac_i] = (ac_i + 1) * 4;

	//assigning array base address to pointer
	ptr_to_array = int_array;

	//displaying values
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i ++)
		printf("int_array[%d] = %d\n", ac_i, *(ptr_to_array + ac_i));

	//diaplaying values with addresses
	printf("\n");
	printf("--- Elements Of Array With Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i ++)
		printf("int_array[%d] = %d\t Address = %p\n", ac_i, *(ptr_to_array + ac_i), (ptr_to_array + ac_i));

	return(0);
}
