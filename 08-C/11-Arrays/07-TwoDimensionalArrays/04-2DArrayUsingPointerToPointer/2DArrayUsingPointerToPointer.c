#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//variable declarations
	int **ptr_int_array = NULL;
	int num_rows, num_columns;
	int ac_i, ac_j;

	//code
	//input: #Rows, #columns 
	printf("\n\n");
	printf("Enter number of Rows for Array: ");
	scanf("%d", &num_rows);

	printf("Enter number of Columns for Array: ");
	scanf("%d", &num_columns);

	//memory allocation
	ptr_int_array = (int **) malloc (sizeof(int) * num_rows);

	if(ptr_int_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed for %d Rows\nExiting...\n", num_rows);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation successful for %d Rows\n", num_rows);
	}

	for(ac_i = 0; ac_i < num_rows; ac_i++)
	{
		ptr_int_array[ac_i] = (int *) malloc(num_columns * sizeof(int)) ;
		
		if(ptr_int_array[ac_i] == NULL)
		{
			printf("\n\n");
			printf("Memory Allocation Failed for columns of Row %d\nExiting...\n", ac_i);
		}

		else
		{
			printf("\n");
			printf("Memory Allocation Successful for columns of Row %d\n", ac_i);
		}
	}

	//assigning values
	for(ac_i = 0; ac_i < num_rows; ac_i++)
	{
		for(ac_j = 0; ac_j < num_columns; ac_j++)
		{
			ptr_int_array[ac_i][ac_j] = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying array
	printf("\n\n");
	for(ac_i = 0; ac_i < num_rows; ac_i++)
	{
		printf("Base Address of %d Row : ptr_int_array[%d] = %p\n", ac_i, ac_i, ptr_int_array[ac_i], &ptr_int_array[ac_i]);
	}

	printf("\n\n");
	for(ac_i = 0; ac_i < num_rows; ac_i++)
	{
		for(ac_j = 0; ac_j < num_columns; ac_j++)
		{
			printf(" ptr_int_array[%d][%d] = %d   at address %p\n", ac_i, ac_j, ptr_int_array[ac_i][ac_j], &ptr_int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//freeing memory
	//for each row
	for(ac_i = (num_rows - 1); ac_i >= 0; ac_i--)
	{
		if(ptr_int_array[ac_i])
		{
			free(ptr_int_array[ac_i]);
			ptr_int_array[ac_i] = NULL;
			printf("Memory Freed: Columns of Row %d\n", ac_i);
		}
	}

	//for base addresses of rows
	if(ptr_int_array)
	{
		free(ptr_int_array);
		ptr_int_array = NULL;
		printf("Memory Freed: ptr_int_array\n");
	}

	return (0);
}
