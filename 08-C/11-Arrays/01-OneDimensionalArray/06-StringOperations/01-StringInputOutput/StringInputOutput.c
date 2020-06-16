#include <stdio.h>

#define AC_MAX_STRING_LENGTH 	512

int main(void)
{
	//variable declaration
	char ch_ac_array[AC_MAX_STRING_LENGTH];
	
	//code
	printf("\n");
	printf("Enter a String: ");
	gets_s(ch_ac_array, AC_MAX_STRING_LENGTH);
	
	printf("\n");
	printf("String entered: %s\n", ch_ac_array);
	
	return (0);
}
