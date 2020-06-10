#include <stdio.h>

#define AC_ARRAY_NUM_ELEMENTS_TYPE_INT      6
#define AC_ARRAY_NUM_ELEMENTS_TYPE_FLOAT    4
#define AC_ARRAY_NUM_ELEMENTS_TYPE_CHAR     10

int main(void)
{
	//variable declarations
	int i_ac_Array[AC_ARRAY_NUM_ELEMENTS_TYPE_INT];
	float f_ac_Array[AC_ARRAY_NUM_ELEMENTS_TYPE_FLOAT];
	char c_ac_Array[AC_ARRAY_NUM_ELEMENTS_TYPE_CHAR];
	int ac_i, ac_num;

	//code
	// ARRAY INPUTS 
	printf("\n\n");
	
	printf("Enter elements for Integer array : \n");

	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_INT; ac_i++)
		scanf("%d", &i_ac_Array[ac_i]);

	printf("\n\n");

	printf("Enter elements for Floating-Point array :\n");
	
	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_FLOAT; ac_i++)
		scanf("%f", &f_ac_Array[ac_i]);
	
	printf("\n\n");
	
	printf("Enter elements for Character Array:\n");
	
	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_CHAR; ac_i++)
	{
		c_ac_Array[ac_i] = getch();
		printf("%c\n", c_ac_Array[ac_i]);
	}
	
	//  ARRAY PRINTING 
	printf("\n\n");
	printf("Integer Array Entered By You :\n");

	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_INT; ac_i++)
		printf("%d  ", i_ac_Array[ac_i]);

	printf("\n\n");
	
	printf("Floating-Point Array Entered By You :\n");
	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_FLOAT; ac_i++)
		printf("%f  ", f_ac_Array[ac_i]);

	printf("\n\n");
	
	printf("Character Array Entered By You :\n");
	for (ac_i = 0; ac_i < AC_ARRAY_NUM_ELEMENTS_TYPE_CHAR; ac_i++)
		printf("%c  ", c_ac_Array[ac_i]);

	printf("\n");
	return(0);
}
