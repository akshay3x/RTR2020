#include <stdio.h>

int main(void)
{
	//variable declarations
	float float_array[10];
	float *ptr_to_farray = NULL;
	int ac_i;

	//code
	//assigning values
	for(ac_i = 0; ac_i < 10; ac_i++)
		float_array[ac_i] = (float)(ac_i + 1) * 1.6f;

	//assigning array base address to pointer
	ptr_to_farray = float_array;

	//displaying array elements
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("float_array[%d] = %f\n", ac_i, *(ptr_to_farray + ac_i));

	//displaying array elements with addresses
	printf("\n\n");
	printf("--- Array Elements with Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("float_array[%d] = %f\t Address = %p\n", ac_i, *(ptr_to_farray + ac_i), (ptr_to_farray + ac_i));

	return (0);
}
