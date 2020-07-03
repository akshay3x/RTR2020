#include <stdio.h>
#include <stdlib.h>

//macro definitions
#define INT_SIZE		sizeof(int)
#define FLOAT_SIZE		sizeof(float)
#define DOUBLE_SIZE		sizeof(double)
#define CHAR_SIZE		sizeof(char)

int main(void)
{
	//variable declarations
	int *ptr_to_int_array = NULL;
	unsigned int int_array_length = 0;

	float *ptr_to_float_array = NULL;
	unsigned int float_array_length = 0;

	double *ptr_to_double_array = NULL;
	unsigned int double_array_length = 0;

	char *ptr_to_char_array = NULL;
	unsigned int char_array_length = 0;
	int ac_i;

	//code
	//integer array
	printf("\n\n");
	printf("Enter the numbers elements for int array: ");
	scanf("%u", &int_array_length);

	//memory allocation
	ptr_to_int_array = (int*) malloc(INT_SIZE * int_array_length);

	if(ptr_to_int_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation For Integer Array Failed!\n Exitng...\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation Successfull\n\n");
	}

	printf("\n");
	printf("Enter %d elements for integer array: \n", int_array_length);
	for(ac_i = 0; ac_i < int_array_length; ac_i++)
	{
		printf("Element %d : ", ac_i + 1);
		scanf("%d", (ptr_to_int_array + ac_i));
	}

	//float array
	printf("\n\n");
	printf("Enter the number of Elements for float array: ");
	scanf("%u", &float_array_length);

	ptr_to_float_array = (float *) malloc(FLOAT_SIZE * float_array_length);

	if(ptr_to_float_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation For float array failed!!!\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation successfull for float array\n\n");
		
	}

	printf("Enter %d Elements for the float array:\n", float_array_length);
	for(ac_i = 0; ac_i < float_array_length; ac_i++)
	{
		printf("Element %d : ", ac_i + 1);
		scanf("%f", (ptr_to_float_array + ac_i));
	}

	//double array
	printf("\n\n");
	printf("Enter number of elements for the Double Array:");
	scanf("%u", &double_array_length);

	ptr_to_double_array = (double *) malloc(DOUBLE_SIZE * double_array_length);

	if(ptr_to_double_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation for Double Array Failed!\n Exiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation for Double Array Successfull!\n\n");
	}

	printf("\n");
	printf("Enter %d Elements for the double array\n", double_array_length);
	for(ac_i = 0; ac_i < double_array_length; ac_i++)
	{
		printf("Element %d: ", ac_i + 1);
		scanf("%lf", (ptr_to_double_array + ac_i ));
	}

	//char array
	printf("\n\n");
	printf("Enter the number of Elements for char array: ");
	scanf("%u", &char_array_length);

	ptr_to_char_array = (char *) malloc(CHAR_SIZE * char_array_length);

	if(ptr_to_float_array == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation For char array failed!!!\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocation successfull for char array\n\n");
		
	}

	printf("Enter %d Elements for the character array:\n", char_array_length);
	for(ac_i = 0; ac_i < char_array_length; ac_i++)
	{
		*(ptr_to_char_array + ac_i) = getch();
		printf(" %c\n", *(ptr_to_char_array + ac_i));
	}

	//displaying arrays
	//int array
	printf("\n\n");
	printf("Integer Array of %d elements is as follows:\n", int_array_length);
	for(ac_i = 0; ac_i < int_array_length; ac_i++)
		printf(" %d\t Address = %p\n", *(ptr_to_int_array + ac_i), (ptr_to_int_array + ac_i));

	//float array
	printf("\n\n");
	printf("Float Array of %d Elements is as follows:\n", float_array_length);
	for(ac_i = 0; ac_i < float_array_length; ac_i++)
		printf(" %f\t Address = %p\n", *(ptr_to_float_array + ac_i), (ptr_to_float_array + ac_i));

	//double array
	printf("\n\n");
	printf("Double array of %d Elements is as follows:\n", double_array_length);
	for(ac_i = 0; ac_i < double_array_length; ac_i++)
		printf(" %lf\t Address = %p\n", *(ptr_to_double_array + ac_i), (ptr_to_double_array + ac_i));

	//char array
	printf("\n\n");
	printf("character array of %d elements is as follows\n", char_array_length);
	for(ac_i = 0; ac_i < char_array_length; ac_i++)
		printf(" %c\t Address = %p\n", *(ptr_to_char_array + ac_i), (ptr_to_char_array + ac_i));

	printf("\n\n");
	printf("--- Momry Deallocation ---\n");
	//freeing memory in reverse order
	if(ptr_to_char_array)
	{
		free(ptr_to_char_array);
		ptr_to_char_array = NULL;
		printf("Memory Freed: Character array\n");
	}

	if(ptr_to_double_array)
	{
		free(ptr_to_double_array);
		ptr_to_double_array = NULL;
		printf("Memory Freed: Double array\n");
	}

	if(ptr_to_float_array)
	{
		free(ptr_to_float_array);
		ptr_to_float_array = NULL;
		printf("Memory Freed: Float array\n");
	}

	if(ptr_to_int_array)
	{
		free(ptr_to_int_array);
		ptr_to_int_array = NULL;
		printf("Memory Freed: Integer array\n");
	}

	return (0);
}
