#include <stdio.h>

int main(void)
{
	//variable declarations
	char char_array[10];
	char *ptr_to_char_array = NULL;
	int ac_i;

	//code
	//assigning values
	for(ac_i = 0; ac_i < 10; ac_i++)
		char_array[ac_i] = (char) (ac_i + 65);

	//assigning base address of array to pointer
	ptr_to_char_array = char_array;

	//displaying elements
	printf("\n\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("char_array[%d] = %c\n", ac_i, *(ptr_to_char_array + ac_i));

	//displaying array elements with addresses
	printf("\n\n");
	printf("--- Array Elements With Addresses ---\n");
	for(ac_i = 0; ac_i < 10; ac_i++)
		printf("char_array[%d] = %c\t Address = %p\n", ac_i, *(ptr_to_char_array + ac_i), (ptr_to_char_array + ac_i));

	return (0);
}
