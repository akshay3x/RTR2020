#include <stdio.h>
#include <conio.h>

//macro definitions
#define AC_NUM_ROWS			6
#define AC_NUM_COLUMNS		4

int main(void)
{
	//variable declarations
	int int_array[AC_NUM_ROWS][AC_NUM_COLUMNS];
	int ac_i, ac_j;

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			*(int_array[ac_i] + ac_j) = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying values with addresses
	printf("\n\n");
	printf("2D Integer Array Elements along with addresses : \n\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf(" *(int_array[%d] + %d) = %d \t At Address (int_address[ac_i] + ac_j) = %p)\n", ac_i, ac_j, *(int_array[ac_i] + ac_j), (int_array[ac_i] + ac_j));
		}
		printf("\n");
	}

	return (0);
}
