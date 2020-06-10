#include <stdio.h>

int main(void)
{
	//variable declaraions
	//IN-LINE INITIALIZATION
	int i_ac_Array[5][3] = { {1, 2, 3}, {2, 4, 6}, {3, 6, 9}, {4, 8, 12}, {5, 10,15} };
	int i_ac_int_size;
	int i_ac_Array_size;
	int i_ac_Array_num_elements, i_ac_Array_num_rows, i_ac_Array_num_columns;

	//code
	printf("\n\n");
	i_ac_int_size = sizeof(int);
	i_ac_Array_size = sizeof(i_ac_Array);
	
	printf("Size Of Two Dimensional ( 2D ) Integer Array Is = %d\n\n", i_ac_Array_size);
	i_ac_Array_num_rows = i_ac_Array_size / sizeof(i_ac_Array[0]);
	
	printf("Number of Rows In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", i_ac_Array_num_rows);
	i_ac_Array_num_columns = sizeof(i_ac_Array[0]) / i_ac_int_size;
	
	printf("Number of Columns In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", i_ac_Array_num_columns);
	i_ac_Array_num_elements = i_ac_Array_num_rows * i_ac_Array_num_columns;

	printf("Number of Elements In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", i_ac_Array_num_elements);
	printf("\n\n");
	printf("Elements In The 2D Array : \n\n");


	printf("------ ROW 1 -----\n");
	printf("iArray[0][0] = %d\n", i_ac_Array[0][0]);
	printf("iArray[0][1] = %d\n", i_ac_Array[0][1]);
	printf("iArray[0][2] = %d\n", i_ac_Array[0][2]);
	printf("\n\n");


	printf("------ ROW 2 ------\n");
	printf("iArray[1][0] = %d\n", i_ac_Array[1][0]);
	printf("iArray[1][1] = %d\n", i_ac_Array[1][1]);
	printf("iArray[1][2] = %d\n", i_ac_Array[1][2]);

	printf("\n\n");

	printf("------ ROW 3 ------\n");
	printf("iArray[2][0] = %d\n", i_ac_Array[2][0]);
	printf("iArray[2][1] = %d\n", i_ac_Array[2][1]);
	printf("iArray[2][2] = %d\n", i_ac_Array[2][2]);
	
	printf("\n\n");

	printf("------ ROW 4 ------\n");
	printf("iArray[3][0] = %d\n", i_ac_Array[3][0]);
	printf("iArray[3][1] = %d\n", i_ac_Array[3][1]);
	printf("iArray[3][2] = %d\n", i_ac_Array[3][2]);

	printf("\n\n");

	printf("------ ROW 5 ------\n");;
	printf("iArray[4][0] = %d\n", i_ac_Array[4][0]);
	printf("iArray[4][1] = %d\n", i_ac_Array[4][1]);
	printf("iArray[4][2] = %d\n", i_ac_Array[4][2]);

	printf("\n\n");

	return(0);
}
