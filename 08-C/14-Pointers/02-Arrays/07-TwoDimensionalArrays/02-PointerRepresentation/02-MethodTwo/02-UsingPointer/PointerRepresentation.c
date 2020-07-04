#include <stdio.h>
#include <stdlib.h>

#define AC_NUM_ROWS			5
#define AC_NUM_COLUMNS		4

int main(void)
{
	//variable declarations
	int **ptr_to_int_array;
	int ac_i, ac_j;

	//code
	//memory allocation
	ptr_to_int_array = (int **) malloc(AC_NUM_ROWS * sizeof(int));

	//memory check
	if(ptr_to_int_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation for 1D array of %d base addresses is failed,\n Exiting now...\n\n", AC_NUM_ROWS);
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation for 1D array of %d base addresses is Successfull\n", AC_NUM_ROWS);
	}

	//allocating memory 
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		//allocating memory for each row
		ptr_to_int_array[ac_i] = (int *) malloc(AC_NUM_COLUMNS * sizeof(int));

		if(ptr_to_int_array[ac_i] == NULL)
		{
			printf("\n");
			printf("Memory Allocation failed for the %d arrow\nExiting Now...\n\n", ac_i);
			exit(0);
		}

		else
		{
			printf("\n");
			printf("Memory allocation for the row %d Successfull\n\n", ac_i);
		}
	}

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			*(*(ptr_to_int_array + ac_i) + ac_j) = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf("(ptr_to_int_array[%d][%d] = %d\t At address &ptr_to_int_array[%d][%d] = %p\n", ac_i, ac_j, ptr_to_int_array[ac_i][ac_j], ac_i, ac_j, &ptr_to_int_array[ac_i][ac_j]);
		}
		printf("\n\n");
	}

	//freeing memory
	for(ac_i = (AC_NUM_ROWS - 1); ac_i >= 0; ac_i--)
	{
		if(*(ptr_to_int_array + ac_i))
		{
			free(*(ptr_to_int_array + ac_i));
			*(ptr_to_int_array + ac_i) = NULL;
			printf("Memory freed: Row %d \n", ac_i);
		}
	}

	if(ptr_to_int_array)
	{
		free(ptr_to_int_array);
		ptr_to_int_array = NULL;
		printf("\n");
		printf("Memory freed: ptr_to_int_array\n");
	}

	return (0);
}
