#include <stdio.h>

int main(void)
{
	//variable declarations
	float float_array[10];
	int ac_i;

	//code
	//assigning Values
	for(ac_i = 0; ac_i < 10; ac_i++)
		float_array[ac_i] = (ac_i + 1) * 1.2001f;

	//displaying array values
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("float_array[%d] = %f\n", ac_i, float_array[ac_i]);

	printf("\n\n");
	printf("--- Array Elements With Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("float_array[%d] = %f\t Address = %p\n", ac_i, float_array[ac_i],&float_array[ac_i]);

	return (0);
}
