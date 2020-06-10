#include <stdio.h>

#define AC_NUM_ELEMENTS 6

int main(void)
{
	//variable declarations
	int i_ac_Array[AC_NUM_ELEMENTS];
	int ac_i, ac_num, ac_sum = 0;

	//code
	printf("\n\n");
	printf("Enter %d Integers for the Array :\n",AC_NUM_ELEMENTS);

	for (ac_i = 0; ac_i < AC_NUM_ELEMENTS; ac_i++)
	{
		scanf("%d", &ac_num);
		i_ac_Array[ac_i] = ac_num;
	}

	for (ac_i = 0; ac_i < AC_NUM_ELEMENTS; ac_i++)
	{
		ac_sum = ac_sum + i_ac_Array[ac_i];
	}

	printf("\n\n");
	printf("Sum of all elements of array = %d\n", ac_sum);

	return(0);
}
