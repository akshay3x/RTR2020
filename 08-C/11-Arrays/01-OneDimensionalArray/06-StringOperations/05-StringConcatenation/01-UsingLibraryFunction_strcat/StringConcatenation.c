#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//variable declarations
	char ch_ac_str_one[AC_MAX_STRING_LENGTH];
	char ch_ac_str_two[AC_MAX_STRING_LENGTH];

	//code
	printf("String Concatination:\n");
	printf("Enter a String:");
	gets_s(ch_ac_str_one, AC_MAX_STRING_LENGTH);

	printf("Enter another String:");
	gets_s(ch_ac_str_two, AC_MAX_STRING_LENGTH);

	printf("\n\n");
	printf("Before Concatination:\n");
	printf("String one: %s\n", ch_ac_str_one);

	printf("\n");
	printf("String Two: %s\n", ch_ac_str_two);

	//concatination library function call
	strcat(ch_ac_str_one, ch_ac_str_two);

	printf("\n");
	printf("After Concatination:\n");
	printf("String one: %s\n", ch_ac_str_one);

	printf("\n");
	printf("String Two: %s\n", ch_ac_str_two);

	return (0);
}
