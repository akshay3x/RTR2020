#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declaration/ prototype
	int AcMyStrLen(char[]);

	//variable declaration
	char ch_ac_array[AC_MAX_STRING_LENGTH];
	int i_ac_string_length = 0;

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_ac_array, AC_MAX_STRING_LENGTH);

	printf("\n");
	printf("String entered by you: %s\n", ch_ac_array);

	//string length
	i_ac_string_length = AcMyStrLen(ch_ac_array);
	printf("Length of the string = %d\n", i_ac_string_length);

	return (0);
}

int AcMyStrLen(char ac_str[])
{
	//variable Declaration
	int ac_j;
	int i_ac_string_length = 0;
	
	//Code
	//'\0' is null terminating character
	for(ac_j = 0; ac_j < AC_MAX_STRING_LENGTH; ac_j++)
	{
		if(ac_str[ac_j] == '\0')
			break;
		else
			i_ac_string_length++;
	}
	
	return(i_ac_string_length);
	
}
