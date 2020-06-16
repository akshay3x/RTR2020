
//Capitalize Each Word's First Letter 

#include <stdio.h>
#include <ctype.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{

	//function declarations
	int AcMyStrLength(char []);

	//variable declarations
	char ch_input_string[AC_MAX_STRING_LENGTH];
	char ch_cap_string[AC_MAX_STRING_LENGTH];
	int ac_i = 0, ac_j = 0;
	int i_input_strlen = 0;

	//code
	printf("\n");
	printf("Enter a string:");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	i_input_strlen = AcMyStrLength(ch_input_string);

	for(ac_i = 0; ac_i < i_input_strlen; ac_i++)
	{
		if(ac_i == 0)
			ch_cap_string[ac_j] = toupper(ch_input_string[ac_i]);
		
		else if(ch_input_string[ac_i] == ' ')
		{
			ch_cap_string[ac_j] = ch_input_string[ac_i];
			ch_cap_string[ac_j + 1] = toupper(ch_input_string[ac_i + 1]);
			
			ac_i++;
			ac_j++;
		}
		
		else
			ch_cap_string[ac_j] = ch_input_string[ac_i];
		
		ac_j++;
	}

	ch_cap_string[ac_j] = '\0';

	printf("\n");
	printf("Entered String:%s\n", ch_input_string);

	printf("\n");
	printf("Capitalised string:%s\n", ch_cap_string);
	
	return (0);
}

int AcMyStrLength(char str[])
{
	//variable declarations
	int ac_i;
	int istrlen = 0;

	//code
	for(ac_i=0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;

		else
			istrlen++;
	}

	return(istrlen);
}
