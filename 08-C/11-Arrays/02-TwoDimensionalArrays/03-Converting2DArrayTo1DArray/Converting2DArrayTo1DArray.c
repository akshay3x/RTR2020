#include <stdio.h>

#define AC_NUM_ROWS		5
#define AC_NUM_COLUMNS	3

int main(void)
{
	//variable declarations
	int i_ac_array_2D[AC_NUM_ROWS][AC_NUM_COLUMNS];
	int i_ac_array_1D[AC_NUM_ROWS * AC_NUM_COLUMNS];
	int ac_i;
	int ac_j;
	int num = 0;

	//code
	printf("\n");
	printf("Enter %d elements for Array:", AC_NUM_ROWS * AC_NUM_COLUMNS);
	
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			scanf("%d", &num);
			i_ac_array_2D[ac_i][ac_j] = num;
		}
	}

	printf("\n");
	printf("Displaying 2D Array:\n");

	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		printf(" %d\t", i_ac_array_2D[ac_i][ac_j]);

		printf("\n");
	}

	//Converting 2D to 1D Array
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			i_ac_array_1D[(ac_i * AC_NUM_COLUMNS) + ac_j] = i_ac_array_2D[ac_i][ac_j];
		}
	}

	//displaying 1D Array
	printf("\n");
	printf("Diplaying 1D Array\n");

	for(ac_j = 0; ac_j < (AC_NUM_ROWS * AC_NUM_COLUMNS); ac_j++)
		{
			printf("1D[%d] = %d\n", ac_j, i_ac_array_1D[ac_j]);
		}

	printf("\n");

	return (0);
}
