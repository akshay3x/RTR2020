#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//variable declaration
	char ch_ac_array[AC_MAX_STRING_LENGTH];
	int i_ac_string_length = 0;

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_ac_array, AC_MAX_STRING_LENGTH);

	printf("\n");
	printf("String entered:%s\n", ch_ac_array);

	//string length
	i_ac_string_length = strlen(ch_ac_array);
	printf("Length of the entered string = %d\n", i_ac_string_length);

	return (0);
}
