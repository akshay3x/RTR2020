#include <stdio.h>

int main(void)
{
	//variable declarations
	char char_array[10];
	int ac_i;

	//code
	//assigning vlues
	for(ac_i = 0; ac_i < 10; ac_i++)
		char_array[ac_i] = (char) (ac_i + 65);

	//displaying values
	printf("\n\n");
	printf("--- Elements of Array ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("char_array[%d] = %c\n", ac_i, char_array[ac_i]);

	//displaying characters with addresses
	printf("\n\n");
	printf("--- Elements of Array With Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("char_array[%d] = %c\t Address = %p\n", ac_i, char_array[ac_i], &char_array[ac_i]);

	return (0);
}
