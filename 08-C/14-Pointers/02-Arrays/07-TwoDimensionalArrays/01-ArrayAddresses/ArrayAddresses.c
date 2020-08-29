#include <stdio.h>

//macro definitions
#define AC_NUM_ROWS		6
#define AC_NUM_COLUMNS	4


int main(void)
{
	//variable declarations
	int int_array[AC_NUM_ROWS][AC_NUM_COLUMNS];
	int ac_i, ac_j;

	//code
	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			int_array[ac_i][ac_j] = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying 2D Array
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		printf("Row-%d\t", ac_i + 1);
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf(" %d\t", int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	//diplaying elements and addresses
	printf("\n\n");
	printf("2D array Elements and Addresses : \n\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf("int_array[%d][%d] = %d\t Address = %p\n", ac_i, ac_j, int_array[ac_i][ac_j], &int_array[ac_i][ac_j]);
		}
		printf("\n");
	}

	return (0);
}