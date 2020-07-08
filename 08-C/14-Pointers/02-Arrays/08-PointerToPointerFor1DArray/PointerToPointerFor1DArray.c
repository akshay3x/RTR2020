#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//function declarations
	void MyAlloc(int **ptr, unsigned int numberOfElements);

	//variable declarations
	int *ptr_int_array = NULL;
	unsigned int num_elements;
	int ac_i;

	//code
	printf("\n");
	printf("How Many Elements you want in integer array: ");
	scanf("%d", &num_elements);

	//user defined function for memory allocation
	MyAlloc(&ptr_int_array, num_elements);

	//array input
	printf("Enter %u Elements for integer array:\n");
	for(ac_i = 0; ac_i < num_elements; ac_i++)
	{
		printf("Element %d:", ac_i + 1);
		scanf("%d", &ptr_int_array[ac_i]);
	}

	//displaying array elements
	printf("\n");
	printf("--- Array Elements ---\n");
	for(ac_i = 0; ac_i < num_elements; ac_i++)
		printf("%d\n", ptr_int_array[ac_i]);

	//freeing memory
	if(ptr_int_array)
	{
		free(ptr_int_array);
		ptr_int_array = NULL;
		printf("\n");
		printf("Memory freed: ptr_int_array");
	}

	return(0);
}

void MyAlloc(int **ptr, unsigned int numberOfElements)
{
	//code
	*ptr = (int *) malloc(numberOfElements * sizeof(int));

	if(*ptr == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: **ptr\n");
		printf("Exiting...\n");
		exit(0);
	}

	printf("Memory Allocation Successful:MyAlloc():size = %d Bytes\n", (numberOfElements * sizeof(int)));
}
