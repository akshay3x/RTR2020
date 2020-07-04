#include <stdio.h>

int main(void)
{
	//variable declarations
	double double_array[10];
	int ac_i;

	//code
	//assigning values
	for(ac_i = 0; ac_i < 10; ac_i++)
		double_array[ac_i] = (float) (ac_i + 1) * 1.666666f;

	//displaying array elements
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf(" double_array[%d] = %lf\n", ac_i, double_array[ac_i]);

	//displaying array elements with addresses
	printf("\n\n");
	printf("--- Array Elements With Addresses---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf(" double_array[%d] = %lf\t Address = %p\n", ac_i, double_array[ac_i], &double_array[ac_i]);

	return (0);
}
