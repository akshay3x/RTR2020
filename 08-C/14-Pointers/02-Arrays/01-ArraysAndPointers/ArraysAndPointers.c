#include <stdio.h>

int main(void)
{
	//variable declarations
	int int_array[] = {13, 26, 39, 52, 65, 78, 91, 104, 117, 130};
	float float_array[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
	double double_array[] = {9.1111, 8.2222, 7.3333, 6.4444};
	char char_array[] = {'A', 'B', 'C', 'D', 'E', 'F'};

	//code
	//displaying arrays using base address of array -> pointers
	//int array
	printf("\n");
	printf("--- Integer Array ---\n");
	printf(" int_array[0] = %d, is at address = %p\n", *(int_array + 0), (int_array + 0));
	printf(" int_array[1] = %d, is at address = %p\n", *(int_array + 1), (int_array + 1));
	printf(" int_array[2] = %d, is at address = %p\n", *(int_array + 2), (int_array + 2));
	printf(" int_array[3] = %d, is at address = %p\n", *(int_array + 3), (int_array + 3));
	printf(" int_array[4] = %d, is at address = %p\n", *(int_array + 4), (int_array + 4));
	printf(" int_array[5] = %d, is at address = %p\n", *(int_array + 5), (int_array + 5));
	printf(" int_array[6] = %d, is at address = %p\n", *(int_array + 6), (int_array + 6));
	printf(" int_array[7] = %d, is at address = %p\n", *(int_array + 7), (int_array + 7));
	printf(" int_array[8] = %d, is at address = %p\n", *(int_array + 8), (int_array + 8));
	printf(" int_array[9] = %d, is at address = %p\n", *(int_array + 9), (int_array + 9));

	//float_array
	printf("\n");
	printf("--- Float Array ---\n");
	printf(" float_array[0] = %f, is at address = %p\n", *(float_array + 0), (float_array + 0));
	printf(" float_array[1] = %f, is at address = %p\n", *(float_array + 1), (float_array + 1));
	printf(" float_array[2] = %f, is at address = %p\n", *(float_array + 2), (float_array + 2));
	printf(" float_array[3] = %f, is at address = %p\n", *(float_array + 3), (float_array + 3));
	printf(" float_array[4] = %f, is at address = %p\n", *(float_array + 4), (float_array + 4));
	printf(" float_array[5] = %f, is at address = %p\n", *(float_array + 5), (float_array + 5));
	printf(" float_array[6] = %f, is at address = %p\n", *(float_array + 6), (float_array + 6));
	printf(" float_array[7] = %f, is at address = %p\n", *(float_array + 7), (float_array + 7));
	printf(" float_array[8] = %f, is at address = %p\n", *(float_array + 8), (float_array + 8));

	//double array
	printf("\n");
	printf("--- Double Array ---\n");
	printf(" double_array[0] = %lf, is at address = %p\n", *(double_array + 0), (double_array + 0));
	printf(" double_array[1] = %lf, is at address = %p\n", *(double_array + 1), (double_array + 1));
	printf(" double_array[2] = %lf, is at address = %p\n", *(double_array + 2), (double_array + 2));
	printf(" double_array[3] = %lf, is at address = %p\n", *(double_array + 3), (double_array + 3));

	//char array
	printf("\n");
	printf("--- Character Array ---\n");
	printf(" char_array[0] = %c, is at address = %p\n", *(char_array + 0), (char_array + 0));
	printf(" char_array[1] = %c, is at address = %p\n", *(char_array + 1), (char_array + 1));
	printf(" char_array[2] = %c, is at address = %p\n", *(char_array + 2), (char_array + 2));
	printf(" char_array[3] = %c, is at address = %p\n", *(char_array + 3), (char_array + 3));
	printf(" char_array[4] = %c, is at address = %p\n", *(char_array + 4), (char_array + 4));
	printf(" char_array[5] = %c, is at address = %p\n", *(char_array + 5), (char_array + 5));

	return (0);
}
