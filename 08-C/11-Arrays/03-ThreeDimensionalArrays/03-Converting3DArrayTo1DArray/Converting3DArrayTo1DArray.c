#include <stdio.h>

#define AC_NUM_ROWS		5
#define AC_NUM_COLUMNS	4
#define AC_DEPTH		3

int main(void)
{
	//variable declaration
	//Inline Initialization of Array
	int i_ac_3D_Array[AC_NUM_ROWS][AC_NUM_COLUMNS][AC_DEPTH] =
								{ { {  1,  2, 41 },	//	----
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

	int ac_i, ac_j, ac_k;
	int i_ac_1D_array[AC_NUM_ROWS * AC_NUM_COLUMNS * AC_DEPTH];

	printf("\n");
	printf("Displaying 3D Array\n");

	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			for(ac_k = 0; ac_k < AC_DEPTH; ac_k++)
			{
				printf("%d  ", i_ac_3D_Array[ac_i][ac_j][ac_k]);
			}
			printf("\n");
		}
		printf("\n");
	}


	for(ac_i = 0; ac_i < AC_NUM_ROWS; ac_i++)
	{
		for(ac_j = 0; ac_j < AC_NUM_COLUMNS; ac_j++)
		{
			for(ac_k = 0; ac_k < AC_DEPTH; ac_k++)
			{
				
				i_ac_1D_array[(ac_i * AC_NUM_COLUMNS * AC_DEPTH) + ( AC_DEPTH * ac_j) + ac_k] = i_ac_3D_Array[ac_i][ac_j][ac_k];
			}
		}
	}

	printf("\n");
	printf("Displaying 1D Array\n");

	for(ac_i = 0; ac_i < AC_NUM_ROWS * AC_NUM_COLUMNS * AC_DEPTH; ac_i++)
	{
		printf("1D_array[%d] = %d \n", ac_i, i_ac_1D_array[ac_i]);
	}

	return (0);
}
