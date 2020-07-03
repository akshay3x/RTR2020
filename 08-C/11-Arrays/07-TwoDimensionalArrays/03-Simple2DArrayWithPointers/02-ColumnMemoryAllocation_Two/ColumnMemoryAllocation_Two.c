#include <stdio.h>
#include <conio.h>

//macro definitions
#define AC_NUM_ROWS				5
#define AC_NUM_COLUMNS_ONE		4
#define AC_NUM_COLUMNS_TWO		6

int main(void)
{
	//variable declarations
	int *int_array[AC_NUM_ROWS];
	int ac_i, ac_j;

	//code
	//array of columns = 4
	printf("\n\n");
	printf("--- FIRST ARRAY ---\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		int_array[ac_i] = (int *) malloc(AC_NUM_COLUMNS_ONE * sizeof(int));
		if(int_array[ac_i] == NULL)
		{
			printf("\n\n");
			printf("Memory allocation failed for the row %d\n Exiting...\n\n", ac_i);
			exit(0);
		}

		else
		{
			printf("\n");
			printf("Memory Allocation successful for row %d\n", ac_i);
		}
	}

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS_ONE; ac_j++)
		{
			int_array[ac_i][ac_j] = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying array
	printf("\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS_ONE; ac_j++)
		{
			printf("int_array[%d][%d] = %d\n", ac_i, ac_j, int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//freeing memory
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		free(int_array[ac_i]);
		int_array[ac_i] = NULL;
		printf("Memory Freed: row %d\n", ac_i);
	}


	printf("\n\n");
	printf("--- SECOND ARRAY ---\n");

	//memory allocation
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		int_array[ac_i] = (int *) malloc(AC_NUM_COLUMNS_TWO * sizeof(int));

		if(int_array[ac_i] == NULL)
		{
			printf("\n");
			printf("Memory Allocation failed for row %d\nExiting...\n\n", ac_i);
		}

		else
		{
			printf("\n");
			printf("Memory allocation for row %d successful\n", ac_i);
		}
	}

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS_TWO; ac_j++)
		{
			int_array[ac_i][ac_j] = (ac_i +1) * (ac_j + 1);
		}
	}

	//displaying array
	printf("\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS_TWO; ac_j++)
		{
			printf("int_array[%d][%d] = %d\n", ac_i, ac_j, int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//freeing memory in reverse order
	for(ac_i = (AC_NUM_ROWS - 1); ac_i >= 0; ac_i--)
	{
		free(int_array[ac_i]);
		int_array[ac_i] = NULL;
		printf("Memory Freed: row %d\n", ac_i);
	}

	return (0);
}
