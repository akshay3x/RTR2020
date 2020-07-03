#include <stdio.h>

int main(void)
{
	//variable declarations
	int int_array[10];
	int ac_i;

	//code
	//assigning values
	for(ac_i = 0; ac_i < 10; ac_i++)
		int_array[ac_i] = 100 * (ac_i + 1);
	
	//displaying values
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf(" int_array[%d] = %d\n", ac_i, int_array[ac_i]);

	//diplaying values with addresses
	printf("\n\n");
	printf("--- Array Elements With Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf(" int_array[%d] = %d\t address = %p\n", ac_i, int_array[ac_i], &int_array[ac_i]);

	return (0);
}
