#include <stdio.h>
#include <conio.h>

//macro definitions
#define AC_NUM_ROWS			5
#define AC_NUM_COLUMNS		4

int main(void)
{
	//variable declarations
	int *int_array[AC_NUM_ROWS];
	int ac_i, ac_j;

	//code
	//memory allocation
	printf("\n\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		int_array[ac_i] = (int *) malloc(AC_NUM_COLUMNS * sizeof(int));

		if(int_array == NULL)
		{
			printf("Memory Allocation Failed For Row %d\nExiting...\n\n", ac_i);
		}

		else
		{
			printf("Memory Allocation Successfull for Row %d\n\n", ac_i);
		}
	}

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			 int_array[ac_i][ac_j] = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying array
	printf("\n\n");
	printf("Displaying 2d array: \n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf("int_array[%d][%d] = %d\n", ac_i, ac_j, int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//freeing memory
	for(ac_i = (AC_NUM_ROWS - 1); ac_i >= 0; ac_i--)
	{
		free(int_array[ac_i]);
		int_array[ac_i] = NULL;
		printf("Memory Freed: row %d\n", ac_i);
	}

	return (0);
}
