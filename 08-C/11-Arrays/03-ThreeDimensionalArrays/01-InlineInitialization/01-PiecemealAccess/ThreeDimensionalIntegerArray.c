#include <stdio.h>

int main(void)
{
	//variable declaration
	//Inline Initialization of Array
	int i_ac_Array[5][4][3] =	{ { {  1,  2, 41 },	//	----
								    {  3,  4, 42 },	//	    | 00th
								    {  5,  6, 43 },	//	    | Row
									{  7,  8, 44 } } ,//----
									
								  { {  9, 10, 45 },	//	----
								    { 11, 12, 46 },	//	    | 01st
								    { 13, 14, 47 },	//	    | Row
								    { 15, 16, 48 } } ,//----
									
								  { { 17, 18, 49 },	//	----
								    { 19, 20, 50 },	//	    | 02nd
								    { 21, 22, 51 },	//	    | Row
								    { 23, 24, 52 } } ,//----
									
								  { { 25, 26, 53 },	//	----
								    { 27, 28, 54 },	//	    | 03rd
								    { 29, 30, 55 },	//	    | Row
								    { 31, 32, 56 } } ,//----
									
								  { { 33, 34, 57 },	//	----
									{ 34, 36, 58 },	//	    | 04th
									{ 37, 38, 59 },	//	    | Row
								    { 39, 40, 60 } }//	----
								};

	int i_ac_int_size;
	int i_ac_array_size;
	int i_ac_num_elements;

	int i_ac_size_of_each_row;
	int i_ac_size_of_each_col;
	int i_ac_size_of_each_dep;

	int i_ac_array_width;
	int i_ac_array_height;
	int i_ac_array_depth;

	//code
	//size of int 
	i_ac_int_size = sizeof(int);

	//size of array
	i_ac_array_size = sizeof(i_ac_Array);

	i_ac_size_of_each_row = sizeof(i_ac_Array[0]);
	i_ac_size_of_each_col = sizeof(i_ac_Array[0][0]);
	i_ac_size_of_each_dep = sizeof(i_ac_Array[0][0][0]);

	//printf("sizeof(i_ac_Array):%d\n", sizeof(i_ac_Array));
	//printf("sizeof(i_ac_Array[0]):%d\n", sizeof(i_ac_Array[0]));
	//printf("sizeof(i_ac_Array[0][0]):%d\n", sizeof(i_ac_Array[0][0]));
	//printf("sizeof(i_ac_Array[0][0][0]):%d\n", sizeof(i_ac_Array[0][0][0]));

	//number of Rows: Array size/size of a row;
	i_ac_array_width  = i_ac_array_size / i_ac_size_of_each_row;

	//Columns in each row: size of a row/size of each column
	i_ac_array_height = i_ac_size_of_each_row / i_ac_size_of_each_col;

	//number of depth:
	i_ac_array_depth  =i_ac_size_of_each_col / i_ac_size_of_each_dep;

	printf("\n");
	printf("width :%d\n", i_ac_array_width);
	printf("height:%d\n", i_ac_array_height);
	printf("depth :%d\n", i_ac_array_depth);

	printf("\n");
	printf("---- ROW-01 ----\n");
	printf("--- column-01 ---\n");
	printf("i_ac_Array[0][0][0] = %d\n", i_ac_Array[0][0][0]);
	printf("i_ac_Array[0][0][1] = %d\n", i_ac_Array[0][0][1]);
	printf("i_ac_Array[0][0][2] = %d\n", i_ac_Array[0][0][2]);

	printf("i_ac_Array[0][1][0] = %d\n", i_ac_Array[0][1][0]);
	printf("i_ac_Array[0][1][1] = %d\n", i_ac_Array[0][1][1]);
	printf("i_ac_Array[0][1][2] = %d\n", i_ac_Array[0][1][2]);

	printf("i_ac_Array[0][2][0] = %d\n", i_ac_Array[0][2][0]);
	printf("i_ac_Array[0][2][1] = %d\n", i_ac_Array[0][2][1]);
	printf("i_ac_Array[0][2][2] = %d\n", i_ac_Array[0][2][2]);

	printf("i_ac_Array[0][3][0] = %d\n", i_ac_Array[0][3][0]);
	printf("i_ac_Array[0][3][1] = %d\n", i_ac_Array[0][3][1]);
	printf("i_ac_Array[0][3][2] = %d\n", i_ac_Array[0][3][2]);

	printf("\n");
	printf("---- ROW-02 ----\n");
	printf("--- column-01 ---\n");
	printf("i_ac_Array[1][0][0] = %d\n", i_ac_Array[1][0][0]);
	printf("i_ac_Array[1][0][1] = %d\n", i_ac_Array[1][0][1]);
	printf("i_ac_Array[1][0][2] = %d\n", i_ac_Array[1][0][2]);

	printf("i_ac_Array[1][1][0] = %d\n", i_ac_Array[1][1][0]);
	printf("i_ac_Array[1][1][1] = %d\n", i_ac_Array[1][1][1]);
	printf("i_ac_Array[1][1][2] = %d\n", i_ac_Array[1][1][2]);

	printf("i_ac_Array[1][3][0] = %d\n", i_ac_Array[1][2][0]);
	printf("i_ac_Array[1][3][1] = %d\n", i_ac_Array[1][2][1]);
	printf("i_ac_Array[1][3][2] = %d\n", i_ac_Array[1][2][2]);

	printf("i_ac_Array[1][4][0] = %d\n", i_ac_Array[1][3][0]);
	printf("i_ac_Array[1][4][1] = %d\n", i_ac_Array[1][3][1]);
	printf("i_ac_Array[1][4][2] = %d\n", i_ac_Array[1][3][2]);

	printf("\n");
	printf("---- ROW-03 ----\n");
	printf("--- column-01 ---\n");
	printf("i_ac_Array[2][0][0] = %d\n", i_ac_Array[2][0][0]);
	printf("i_ac_Array[2][0][1] = %d\n", i_ac_Array[2][0][1]);
	printf("i_ac_Array[2][0][2] = %d\n", i_ac_Array[2][0][2]);

	printf("i_ac_Array[2][1][0] = %d\n", i_ac_Array[2][1][0]);
	printf("i_ac_Array[2][1][1] = %d\n", i_ac_Array[2][1][1]);
	printf("i_ac_Array[2][1][2] = %d\n", i_ac_Array[2][1][2]);

	printf("i_ac_Array[2][2][0] = %d\n", i_ac_Array[2][2][0]);
	printf("i_ac_Array[2][2][1] = %d\n", i_ac_Array[2][2][1]);
	printf("i_ac_Array[2][2][2] = %d\n", i_ac_Array[2][2][2]);

	printf("i_ac_Array[2][3][0] = %d\n", i_ac_Array[2][3][0]);
	printf("i_ac_Array[2][3][1] = %d\n", i_ac_Array[2][3][1]);
	printf("i_ac_Array[2][3][2] = %d\n", i_ac_Array[2][3][2]);

	printf("\n");
	printf("---- ROW-04 ----\n");
	printf("--- column-01 ---\n");
	printf("i_ac_Array[3][0][0] = %d\n", i_ac_Array[3][0][0]);
	printf("i_ac_Array[3][0][1] = %d\n", i_ac_Array[3][0][1]);
	printf("i_ac_Array[3][0][2] = %d\n", i_ac_Array[3][0][2]);

	printf("i_ac_Array[3][1][0] = %d\n", i_ac_Array[3][1][0]);
	printf("i_ac_Array[3][1][1] = %d\n", i_ac_Array[3][1][1]);
	printf("i_ac_Array[3][1][2] = %d\n", i_ac_Array[3][1][2]);

	printf("i_ac_Array[3][2][0] = %d\n", i_ac_Array[3][2][0]);
	printf("i_ac_Array[3][2][1] = %d\n", i_ac_Array[3][2][1]);
	printf("i_ac_Array[3][2][2] = %d\n", i_ac_Array[3][2][2]);

	printf("i_ac_Array[3][3][0] = %d\n", i_ac_Array[3][3][0]);
	printf("i_ac_Array[3][3][1] = %d\n", i_ac_Array[3][3][1]);
	printf("i_ac_Array[3][3][2] = %d\n", i_ac_Array[3][3][2]);

	printf("\n");
	printf("---- ROW-05 ----\n");
	printf("--- column-01 ---\n");
	printf("i_ac_Array[4][0][0] = %d\n", i_ac_Array[4][0][0]);
	printf("i_ac_Array[4][0][1] = %d\n", i_ac_Array[4][0][1]);
	printf("i_ac_Array[4][0][2] = %d\n", i_ac_Array[4][0][2]);

	printf("i_ac_Array[4][1][0] = %d\n", i_ac_Array[4][1][0]);
	printf("i_ac_Array[4][1][1] = %d\n", i_ac_Array[4][1][1]);
	printf("i_ac_Array[4][1][2] = %d\n", i_ac_Array[4][1][2]);

	printf("i_ac_Array[4][2][0] = %d\n", i_ac_Array[4][2][0]);
	printf("i_ac_Array[4][2][1] = %d\n", i_ac_Array[4][2][1]);
	printf("i_ac_Array[4][2][2] = %d\n", i_ac_Array[4][2][2]);

	printf("i_ac_Array[4][3][0] = %d\n", i_ac_Array[4][3][0]);
	printf("i_ac_Array[4][3][1] = %d\n", i_ac_Array[4][3][1]);
	printf("i_ac_Array[4][3][2] = %d\n", i_ac_Array[4][3][2]);

	printf("\n");

	return (0);

}
