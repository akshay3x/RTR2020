#include <stdio.h>
#include <conio.h>

//macro definitions
#define AC_NUM_ROWS			5
#define AC_NUM_COLUMNS		6

int main(void)
{
	//varable declarations
	int *int_array[AC_NUM_ROWS];
	int ac_i, ac_j;

	//code
	//memory allocation for 2D array
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		int_array[ac_i] = (int *) malloc((AC_NUM_COLUMNS - ac_i) * sizeof(int));

		if(int_array[ac_i] == NULL)
		{
			printf("\n\n");
			printf("Memory Allocation for Row/Array %d Failed\nExiting...\n\n", ac_i);
		}

		else
		{
			printf("\n");
			printf("Memory allocation successful for Row/Array %d\n", ac_i);
		}
		
	}

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < (AC_NUM_COLUMNS - ac_i); ac_j++)
		{
			int_array[ac_i][ac_j] = (ac_i + 1) * (ac_j + 1);
		}
	}

	//diplaying array
	printf("\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		printf("--- row %d ---\n", ac_i);
		for(ac_j = 0; ac_j < (AC_NUM_COLUMNS - ac_i); ac_j++)
		{
			printf("int_array[%d][%d] = %d\n", ac_i, ac_j, int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//freeing memory
	printf("\n");
	for(ac_i = (AC_NUM_ROWS - 1); ac_i >= 0; ac_i--)
	{
		if(int_array[ac_i])
		{
			free(int_array[ac_i]);
			int_array[ac_i] = NULL;
			printf("Memory Freed: row %d\n", ac_i);
		}
	}

	return (0);
}