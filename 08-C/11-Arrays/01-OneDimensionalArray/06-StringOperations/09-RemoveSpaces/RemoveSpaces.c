#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations
	int AcMyStringLength(char []);
	void AcMystrcpy(char [], char[]);

	//variable declarations
	char ch_input_string[AC_MAX_STRING_LENGTH];
	char ch_space_rmv_string[AC_MAX_STRING_LENGTH];
	int ac_i = 0;
	int ac_j = 0;
	int i_input_string_length = 0;

	//code
	printf("Enter a String:");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	i_input_string_length = AcMyStringLength(ch_input_string);
	ac_j = 0;

	for(ac_i = 0; ac_i < i_input_string_length; ac_i++)
	{
		if(ch_input_string[ac_i] == ' ')
			continue;
		else
		{
			ch_space_rmv_string[ac_j] = ch_input_string[ac_i];
			ac_j++;
		}
	}
	ch_space_rmv_string[ac_j] = '\0';

	printf("\n\n");
	printf("Entered String:%s\n", ch_input_string);
	printf("Space removed string:%s\n\n", ch_space_rmv_string);

	return (0);
}

int AcMyStringLength(char str[])
{
	//variable declarations
	int istrlen = 0;
	int ac_i;

	//code
	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			istrlen++;
		
	}

	return (istrlen);
}