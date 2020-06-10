#include <stdio.h>
int main(void)
{
	//variable declaraions
	int ac_i, ac_j;
	int i_ac_Array[5][3] = { {1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5} }; //IN-LINE INITIALIZATION
	int i_ac_int_size;
	int i_ac_Array_size;
	int i_ac_Array_num_elements, i_ac_Array_num_rows, i_ac_Array_num_columns;

	//code
	printf("\n");
	
	i_ac_int_size = sizeof(int);
	i_ac_Array_size = sizeof(i_ac_Array);
	i_ac_Array_num_rows = i_ac_Array_size / sizeof(i_ac_Array[0]);
	i_ac_Array_num_columns = sizeof(i_ac_Array[0]) / i_ac_int_size;
	i_ac_Array_num_elements = i_ac_Array_num_rows * i_ac_Array_num_columns;

	printf("Size of Array  = %d\n", i_ac_Array_size);
	printf("Number of Rows = %d\n",i_ac_Array_num_rows);
	printf("Number of Columns = %d\n", i_ac_Array_num_columns);
	printf("Number of Elements = %d\n", i_ac_Array_num_elements);

	printf("\n\n");
	printf("Elements In The 2D Array : \n\n");

	for (ac_i = 0; ac_i < i_ac_Array_num_rows; ac_i++)
	{
		printf("---- Row %d -----\n", (ac_i + 1));
		
		for (ac_j = 0; ac_j < i_ac_Array_num_columns; ac_j++)
		{
			printf("iArray[%d][%d] = %d\n", ac_i, ac_j, i_ac_Array[ac_i][ac_j]);
		}
		printf("\n\n");
	}

	printf("Array: Rows * Columns:\n");
	
	for (ac_i = 0; ac_i < i_ac_Array_num_rows; ac_i++)
	{
		for (ac_j = 0; ac_j < i_ac_Array_num_columns; ac_j++)
		{
			printf( " %d ",i_ac_Array[ac_i][ac_j]);
		}
		printf("\n");
	}

	return(0);
}
