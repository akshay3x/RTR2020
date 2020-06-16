#include<stdio.h>

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

	int  i_ac_array_width;
	int  i_ac_array_height;
	int  i_ac_array_depth;

	int ac_i, ac_j, ac_k;

	//code
	printf("\n\n");
	i_ac_int_size = sizeof(i_ac_Array);

	printf("Size of Array = %d", i_ac_int_size);
	
	i_ac_array_width = i_ac_int_size / sizeof(i_ac_Array[0]);

	i_ac_array_height = sizeof(i_ac_Array[0]) / sizeof(i_ac_Array[0][0]);
	
	i_ac_array_depth = sizeof(i_ac_Array[0][0])/ sizeof(i_ac_Array[0][0][0]);

	printf("\n");
	printf("Array Width: %d \n", i_ac_array_width );
	printf("Array Height: %d \n", i_ac_array_height);
	printf("Array Depth: %d \n", i_ac_array_depth);

	printf("\n");
	printf("----------\n");
	for(ac_i = 0; ac_i < i_ac_array_width; ac_i++)
	{
		for(ac_j = 0; ac_j < i_ac_array_height; ac_j++)
		{
			for(ac_k = 0; ac_k < i_ac_array_depth; ac_k++)
			{
				printf("i_ac_Array[%d][%d][%d] = %d\n", ac_i, ac_j, ac_k, i_ac_Array[ac_i][ac_j][ac_k]);
			}
			printf("\n");
		}
		printf("----------\n");
	}

	return (0);
}
