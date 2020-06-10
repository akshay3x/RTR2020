#include <stdio.h>

int main(void)
{
	//variable declaraions
	int i_ac_Array[] = { 18, 25, 8, 11, 78, 97, 119, 63, 9, 49 };
	int i_ac_IntSize;
	int i_ac_Array_size;
	int i_ac_Array_num_elements;

	float f_ac_Array[] = { 2.9f, 3.8f, 7.6f, 8.8f, 1.6f, 0.7f, 7.8f, 8.1f, 2.3f, 8.3f,  98.6987f, 789.321f, 98.32f, 58.3f};
	int f_ac_FloatSize;
	int f_ac_Array_size;
	int f_ac_Array_num_elements;

	char c_ac_Array[] = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P' };
	int c_ac_CharSize;
	int c_ac_Array_size;
	int c_ac_Array_num_elements;

	//code
	printf("\n\n");
	printf("In-line Initialization And Piece-meal Display Of Elements of iArray[]:\n");
	printf("Array[0] = %d\n", i_ac_Array[0]);
	printf("Array[1] = %d\n", i_ac_Array[1]);
	printf("Array[2] = %d\n", i_ac_Array[2]);
	printf("Array[3] = %d\n", i_ac_Array[3]);
	printf("Array[4] = %d\n", i_ac_Array[4]);
	printf("Array[5] = %d\n", i_ac_Array[5]);
	printf("Array[6] = %d\n", i_ac_Array[6]);
	printf("Array[7] = %d\n", i_ac_Array[7]);
	printf("Array[8] = %d\n", i_ac_Array[8]);
	printf("Array[9] = %d\n", i_ac_Array[9]);

	i_ac_IntSize = sizeof(int);
	i_ac_Array_size = sizeof(i_ac_Array);
	i_ac_Array_num_elements = i_ac_Array_size / i_ac_IntSize;

	printf("\n");
	printf("Size Of int data type = %d bytes\n", i_ac_IntSize);
	printf("Number of elements %d \n", i_ac_Array_num_elements);
	printf("Size Of iArray[] (%d Elements * %d Bytes) = %d Bytes\n", i_ac_Array_num_elements, i_ac_IntSize, i_ac_Array_size);


	printf("\n");
	printf("In-line Initialization And Piece-meal Display fArray[]:\n");
	printf("fArray[0] = %f\n", f_ac_Array[0]);
	printf("fArray[1] = %f\n", f_ac_Array[1]);
	printf("fArray[2] = %f\n", f_ac_Array[2]);
	printf("fArray[3] = %f\n", f_ac_Array[3]);
	printf("fArray[4] = %f\n", f_ac_Array[4]);
	printf("fArray[5] = %f\n", f_ac_Array[5]);
	printf("fArray[6] = %f\n", f_ac_Array[6]);
	printf("fArray[7] = %f\n", f_ac_Array[7]);
	printf("fArray[8] = %f\n", f_ac_Array[8]);
	printf("fArray[9] = %f\n", f_ac_Array[9]);

	f_ac_FloatSize = sizeof(float);
	f_ac_Array_size = sizeof(f_ac_Array);
	f_ac_Array_num_elements = f_ac_Array_size / f_ac_FloatSize;
	
	printf("\n");
	printf("Size Of float data type = %d bytes\n", f_ac_FloatSize);
	printf("Number Of Elements = %d Elements\n", f_ac_Array_num_elements);
	printf("Size Of fArray[] (%d Elements * %d Bytes) = %d Bytes\n\n", f_ac_Array_num_elements, f_ac_FloatSize, f_ac_Array_size);


	printf("\n\n");
	printf("In-line Initialization And Piece-meal Display Of Elements of Array'cArray[]': \n");
	printf("cArray[0]  = %c\n", c_ac_Array[0]);
	printf("cArray[1]  = %c\n", c_ac_Array[1]);
	printf("cArray[2]  = %c\n", c_ac_Array[2]);
	printf("cArray[3]  = %c\n", c_ac_Array[3]);
	printf("cArray[4]  = %c\n", c_ac_Array[4]);
	printf("cArray[5]  = %c\n", c_ac_Array[5]);
	printf("cArray[6]  = %c\n", c_ac_Array[6]);
	printf("cArray[7]  = %c\n", c_ac_Array[7]);
	printf("cArray[8]  = %c\n", c_ac_Array[8]);
	printf("cArray[9]  = %c\n", c_ac_Array[9]);
	printf("cArray[10] = %c\n", c_ac_Array[10]);
	printf("cArray[11] = %c\n", c_ac_Array[11]);
	printf("cArray[12] = %c\n", c_ac_Array[12]);

	printf("\n");
	c_ac_CharSize = sizeof(char);
	c_ac_Array_size = sizeof(c_ac_Array);
	c_ac_Array_num_elements = c_ac_Array_size / c_ac_CharSize;
	
	printf("\n");
	printf("Size Of char data type = %d bytes\n", c_ac_CharSize);
	printf("Number Of Elements = %d Elements\n", c_ac_Array_num_elements);
	printf("Size Of cArray[] (%d Elements * %d Bytes) = %d Bytes\n\n", c_ac_Array_num_elements, c_ac_CharSize, c_ac_Array_size);

	return(0);
}

