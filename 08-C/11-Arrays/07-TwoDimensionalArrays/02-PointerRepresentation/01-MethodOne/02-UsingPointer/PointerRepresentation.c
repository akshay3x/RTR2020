#include <stdio.h>

//macro definitions
#define AC_NUM_ROWS			5
#define AC_NUM_COLUMNS		4

int main(void)
{
	//varable declarations
	int int_array[AC_NUM_ROWS][AC_NUM_COLUMNS];
	int ac_i, ac_j;
	int *ptr_to_int_array_row = NULL;

	//assigning values
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		//assigning row base address to pointer
		ptr_to_int_array_row = int_array[ac_i];

		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			*(ptr_to_int_array_row + ac_j) = (ac_i + 1) * (ac_j + 1);
		}
	}

	//displaying values
	printf("\n\n");
	printf("2D integer array elements along with addresses : \n\n");
	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		//assigning row base address to pointer
		ptr_to_int_array_row = int_array[ac_i];

		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			printf(" *(ptr_to_int_array_row + %d) = %d\t Address (ptr_to_int_array_row + %d): %p\n", ac_j, *(ptr_to_int_array_row + ac_j), ac_j, (ptr_to_int_array_row + ac_j));
		}
		printf("\n");
	}

	return (0);
}
