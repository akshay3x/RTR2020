#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//variable declaration
	char ch_ac_str_org[AC_MAX_STRING_LENGTH];

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_ac_str_org, AC_MAX_STRING_LENGTH);

	printf("\n");
	printf("String entered : %s\n", ch_ac_str_org);

	printf("\n");
	//reverse function call inside the printf()
	printf("Copied string : %s\n", strrev(ch_ac_str_org));

	return (0);
}