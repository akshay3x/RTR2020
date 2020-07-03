#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//function declarations
	void MultiplyArrayElementsByNumber(int *, int, int);

	//variable declarations
	int *int_array = NULL;
	int ac_num_elements;
	int ac_i, ac_num;

	//code
	printf("\n");

	printf("Enter Number of Elements for integer array: ");
	scanf("%d", &ac_num_elements);

	int_array = (int *) malloc(ac_num_elements * sizeof(int));

	if(int_array == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: int_array\n");
		printf("Exiting...\n");
		exit(0);
	}

	printf("\n");
	printf("Enter %d Elements:\n", ac_num_elements);
	for(ac_i = 0; ac_i < ac_num_elements; ac_i++)
	{
		printf(" Element %d: ", ac_i + 1);
		scanf("%d", &int_array[ac_i]);
	}

	//displaying array
	printf("\n");
	printf("Displaying Array\n");
	for(ac_i = 0; ac_i < ac_num_elements; ac_i++)
	{
		printf(" int_array[%d] = %d\n", ac_i, int_array[ac_i]);
	}

	printf("\n");
	printf("Enter the number to multiply each member of array: ");
	scanf("%d", &ac_num);

	//function call
	MultiplyArrayElementsByNumber(int_array, ac_num_elements, ac_num);

	printf("\n");
	printf("Displaying Multiplied Array\n");
	for(ac_i = 0; ac_i < ac_num_elements; ac_i++)
	{
		printf(" int_array[%d] = %d\n", ac_i, int_array[ac_i]);
	}

	//freeing memory
	if(int_array)
	{
		free(int_array);
		int_array = NULL;
		printf("\n");
		printf("Memory Freed: int_array\n");
	}

	return(0);
}

void MultiplyArrayElementsByNumber(int *array, int num_elements, int n)
{
	//variable declarations
	int ac_i;

	//code
	for(ac_i = 0; ac_i < num_elements; ac_i++)
	{
		array[ac_i] = array[ac_i] * n;
	}
}
