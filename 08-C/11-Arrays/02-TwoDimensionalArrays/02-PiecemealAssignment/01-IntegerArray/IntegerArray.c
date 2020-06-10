#include <stdio.h>

int main(void)
{
	//variable declaraions
	int i_ac_Array[3][5];
	int i_ac_int_size;
	int i_ac_Array_size;
	int i_ac_num_elements, i_ac_num_rows, i_ac_num_columns;
	int ac_i, ac_j;

	//code
	printf("\n\n");
	i_ac_int_size = sizeof(int);
	i_ac_Array_size = sizeof(i_ac_Array);
	i_ac_num_rows = i_ac_Array_size / sizeof(i_ac_Array[0]);
	i_ac_num_columns = sizeof(i_ac_Array[0]) / i_ac_int_size;
	i_ac_num_elements = i_ac_num_rows * i_ac_num_columns;

	printf("Size Of Array = %d\n\n",i_ac_Array_size);
	printf("Number of Rows = %d\n\n", i_ac_num_rows);
	printf("Number of Columns = %d\n\n", i_ac_num_columns);
	printf("Number of Elements = %d\n\n", i_ac_num_elements);

	printf("\n\n");
	printf("Elements In The 2D Array :\n");
	

	i_ac_Array[0][0] = 31;
	i_ac_Array[0][1] = 62;
	i_ac_Array[0][2] = 93;
	i_ac_Array[0][3] = 124;
	i_ac_Array[0][4] = 155;


	i_ac_Array[1][0] = 32;
	i_ac_Array[1][1] = 64;
	i_ac_Array[1][2] = 96;
	i_ac_Array[1][3] = 128;
	i_ac_Array[1][4] = 160;
	

	i_ac_Array[2][0] = 33;
	i_ac_Array[2][1] = 66;
	i_ac_Array[2][2] = 99;
	i_ac_Array[2][3] = 132;
	i_ac_Array[2][4] = 165;


	for (ac_i = 0; ac_i < i_ac_num_rows; ac_i++)
	{
		printf("----- ROW %d -----\n", (ac_i + 1));
		for (ac_j = 0; ac_j < i_ac_num_columns; ac_j++)
		{
			printf("iArray[%d][%d] = %d\n", ac_i, ac_j, i_ac_Array[ac_i][ac_j]);
		}
		printf("\n\n");
	}
	
	printf("ARRAY:\n");
	for (ac_i = 0; ac_i < i_ac_num_rows; ac_i++)
	{
		for (ac_j = 0; ac_j < i_ac_num_columns; ac_j++)
		{
			printf("%d  ", i_ac_Array[ac_i][ac_j]);
		}
		printf("\n");
	}

	return(0);
}
