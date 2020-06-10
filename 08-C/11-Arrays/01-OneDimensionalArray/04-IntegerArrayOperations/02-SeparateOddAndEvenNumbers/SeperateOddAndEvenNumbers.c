#include <stdio.h>

#define AC_NUM_ELEMENTS   12

int main(void)
{
	//variable declarations
	int i_ac_Array[AC_NUM_ELEMENTS];
	int ac_i, ac_num = 0;

	//code
	printf("\n\n");
	// ARRAY INPUT
	printf("Enter %d Integers:\n", AC_NUM_ELEMENTS);

	for (ac_i = 0; ac_i < AC_NUM_ELEMENTS; ac_i++)
	{
		scanf("%d", &ac_num);
		i_ac_Array[ac_i] = ac_num;
	}

	// SEPARATING EVEN NUMBERS
	printf("\n\n");
	printf("Even numbers are:\n");
	for (ac_i = 0; ac_i < AC_NUM_ELEMENTS; ac_i++)
	{
		if ((i_ac_Array[ac_i] % 2) == 0)
			printf("%d  ", i_ac_Array[ac_i]);
	}
	
	//SEPARATING ODD NUMBERS
	printf("\n\n");
	printf("Odd numbers are:\n");
	for (ac_i = 0; ac_i < AC_NUM_ELEMENTS; ac_i++)
	{
		if ((i_ac_Array[ac_i] % 2) != 0)
			printf("%d  ", i_ac_Array[ac_i]);
	}

	return(0);
}
