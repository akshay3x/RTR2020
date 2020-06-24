#include <stdio.h>
#include <stdlib.h>

//macros
#define AC_INT_ARRAY_SIZE		5
#define AC_FLOAT_ARRAY_SIZE		8
#define AC_CHAR_ARRAY_SIZE		26

#define AC_NUM_STRINGS				10
#define AC_CHARS_STRING_PER_STRING	30

#define ALPHABET_BEGINNING 65 //for char 'A'

//struct declarations
struct struct_data1
{
	int i_ac_array[AC_INT_ARRAY_SIZE];
	float f_ac_array[AC_FLOAT_ARRAY_SIZE];
};

struct struct_data2
{
	char c_ac_array[AC_CHAR_ARRAY_SIZE];
	char c_ac_str_array[AC_NUM_STRINGS][AC_CHARS_STRING_PER_STRING];
};

int main(void)
{
	//variable declarations
	struct struct_data1 data1;
	struct struct_data2 data2;

	int ac_i;

	//code
	//piece-meal assignment, hard-coded
	data1.i_ac_array[0] = 1;
	data1.i_ac_array[1] = 2;
	data1.i_ac_array[2] = 3;
	data1.i_ac_array[3] = 4;
	data1.i_ac_array[4] = 5;

	//loop assignment, user inputs
	printf("\n");
	printf("Enter %d float values for the array\n", AC_FLOAT_ARRAY_SIZE);
	for(ac_i =0; ac_i < AC_FLOAT_ARRAY_SIZE; ac_i++)
		scanf("%f", &data1.f_ac_array[ac_i]);

	//loop assignment, hardcoded
	for(ac_i =0; ac_i < AC_CHAR_ARRAY_SIZE; ac_i++)
		data2.c_ac_array[ac_i] = (char)(ac_i + ALPHABET_BEGINNING);

	//piece meal, assignment hardcodded 
	strcpy(data2.c_ac_str_array[0], "Welcome, 1 ");
	strcpy(data2.c_ac_str_array[1], "Welcome, 2");
	strcpy(data2.c_ac_str_array[2], "Welcome, 3");
	strcpy(data2.c_ac_str_array[3], "Welcome, 4");
	strcpy(data2.c_ac_str_array[4], "Welcome, 5");
	strcpy(data2.c_ac_str_array[5], "Welcome, 6");
	strcpy(data2.c_ac_str_array[6], "Welcome, 7");
	strcpy(data2.c_ac_str_array[7], "Welcome, 8");
	strcpy(data2.c_ac_str_array[8], "Welcome, 9");
	strcpy(data2.c_ac_str_array[9], "Welcome, 10");


	printf("\n");
	printf("\n");

	//data1.i_ac_array
	printf("Displaying the data1 integer members\n");
	for(ac_i =0; ac_i < AC_INT_ARRAY_SIZE; ac_i++)
		printf("data1.i_ac_array [%d] = %d\n", ac_i,  data1.i_ac_array [ac_i]);

	//data1.f_ac_array
	printf("\n\n");
	printf("Displaying data1 float members\n");
	for(ac_i =0; ac_i < AC_FLOAT_ARRAY_SIZE; ac_i++)
		printf("data1.f_ac_array [%d] = %f\n", ac_i,  data1.f_ac_array [ac_i]);

	//data2.c_ac_array
	printf("\n\n");
	printf("Displaying data2 char array members\n");
	for(ac_i =0; ac_i < AC_CHAR_ARRAY_SIZE; ac_i++)
		printf("data2.c_ac_array [%d] = %c\n", ac_i,  data2.c_ac_array [ac_i]);

	//data2.c_ac_str_array
	printf("\n\n");
	printf("Displaying the dta2 string members\n");
	for(ac_i =0; ac_i < AC_NUM_STRINGS; ac_i++)
		printf("data2.c_ac_str_array [%d] = %s\n", ac_i,  data2.c_ac_str_array [ac_i]);

	printf("\n");

	return(0);
}
