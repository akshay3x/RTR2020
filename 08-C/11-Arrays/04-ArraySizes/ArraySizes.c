#include <stdio.h>

int main(void)
{
	int i_ac_1D_array[6];
	int i_ac_2D_array[40][50];
	int i_ac_3D_array[15][26][50];
	
	int i_ac_num_rows2d;
	int i_ac_num_rows3d;
	
	int i_ac_num_cols2d;
	int i_ac_num_cols3d;
	
	int i_ac_depth3d;
	
	int i_ac_num_elements1d;
	int i_ac_num_elements2d;
	int i_ac_num_elements3d;
	
	//1D Array
	i_ac_num_elements1d = sizeof(i_ac_1D_array) / sizeof(i_ac_1D_array[0]);
	
	
	//2D Array
	i_ac_num_rows2d = sizeof(i_ac_2D_array) / sizeof(i_ac_2D_array[0]);
	i_ac_num_cols2d = sizeof(i_ac_2D_array[0]) / sizeof(i_ac_2D_array[0][0]);
	i_ac_num_elements2d = i_ac_num_rows2d * i_ac_num_cols2d;
	
	//3D Array
	i_ac_num_rows3d = sizeof(i_ac_3D_array) / sizeof(i_ac_3D_array[0]);
	i_ac_num_cols3d = sizeof(i_ac_3D_array[0]) / sizeof(i_ac_3D_array[0][0]);
	i_ac_depth3d = sizeof(i_ac_3D_array[0][0]) / sizeof(i_ac_3D_array[0][0][0]);
	i_ac_num_elements3d = i_ac_num_rows3d * i_ac_num_cols3d * i_ac_depth3d;

	printf("\n");
	printf("--- 1D-Array ---\n");
	printf("Number Of Elements in 1D Array:	%d\n", i_ac_num_elements1d);
	
	printf("\n");
	printf("--- 2D-Array ---\n");
	printf("Number of Rows in 2D Array:	%d\n", i_ac_num_rows2d);
	printf("Number of Columns in 2D Array:	%d\n", i_ac_num_cols2d);
	printf("Number Of Elements in 2D Array:	%d\n", i_ac_num_elements2d);
	
	printf("\n");
	printf("--- 3D-Array ---\n");
	printf("Number of Rows in 3D Array:	%d\n", i_ac_num_rows3d);
	printf("Number of Columns in 3D Array:	%d\n", i_ac_num_cols3d);
	printf("Depth of 3D Array:		%d\n", i_ac_depth3d);
	printf("Number Of Elements in 3D Array:	%d\n", i_ac_num_elements3d);

	return (0);
}