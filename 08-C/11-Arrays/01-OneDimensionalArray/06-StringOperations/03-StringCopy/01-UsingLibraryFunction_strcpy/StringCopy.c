#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//variable declaration
	char ch_ac_str_org[AC_MAX_STRING_LENGTH];
	char ch_ac_str_copy[AC_MAX_STRING_LENGTH];

	//code
	printf("\n");
	printf("Enter a String: ");
	gets_s(ch_ac_str_org, AC_MAX_STRING_LENGTH);

	//copying
	strcpy(ch_ac_str_copy, ch_ac_str_org);

	printf("\n");
	printf("String entered: %s\n", ch_ac_str_org);

	printf("\n");
	printf("Copied string: %s\n", ch_ac_str_copy);

	return (0);
}
