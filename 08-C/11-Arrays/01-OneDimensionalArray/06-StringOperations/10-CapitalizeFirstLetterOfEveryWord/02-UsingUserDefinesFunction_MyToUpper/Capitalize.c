
//Capitalize Each Word's First Letter.

#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

#define AC_SPACE 				' '
#define AC_FULLSTOP 			'.'
#define AC_COMMA 				','
#define AC_EXCLAMATION 			'!'
#define AC_QUESTION_MARK 		'?'

int main(void)
{
	//function declaration/prototype
	int AcMyStringLength(char []);
	char AcMyToUpper(char);

	//Variable Declaration
	char ch_input_string[AC_MAX_STRING_LENGTH];
	char ch_caps_string[AC_MAX_STRING_LENGTH];
	int ac_i = 0, ac_j = 0;
	int istrlen = 0;

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	istrlen = AcMyStringLength(ch_input_string);

	for(ac_i = 0; ac_i < istrlen; ac_i++)
	{
		if(ac_i == 0)
			ch_caps_string[ac_j] = AcMyToUpper(ch_input_string[ac_i]);

		else if(ch_input_string[ac_i] == AC_SPACE)
		{
			ch_caps_string[ac_j] = ch_input_string[ac_i];
			ch_caps_string[ac_j + 1] = AcMyToUpper(ch_input_string[ac_i + 1]);
			ac_i++;
			ac_j++;
		}

		else if((ch_input_string[ac_i] == AC_QUESTION_MARK ) ||
				(ch_input_string[ac_i] == AC_FULLSTOP ) ||
				(ch_input_string[ac_i] == AC_COMMA ) ||
				(ch_input_string[ac_i] == AC_EXCLAMATION ))
		{
			ch_caps_string[ac_j] = ch_input_string[ac_i];
			ch_caps_string[ac_j+1] = AC_SPACE ;
			ch_caps_string[ac_j + 2] = AcMyToUpper(ch_input_string[ac_i + 1]);
			ac_j = ac_j + 2;
			ac_i++;
		}

		else
			ch_caps_string[ac_j] = ch_input_string[ac_i];

		ac_j++;
	}
	ch_caps_string[ac_j] = '\0';

	printf("\n");
	printf("Entered String: %s\n", ch_input_string);

	printf("Capitalized String: %s\n", ch_caps_string);
	
	return (0);

}

int AcMyStringLength(char str[])
{
	//Variable Declaration
	int istrlen = 0;
	int ac_i;

	//code
	for(ac_i=0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			istrlen++;
	}

	return istrlen;
}

char AcMyToUpper(char ch)
{
	//Variable Declaration
	int idiff = 0;
	int ac_c;

	//code
	idiff = 'a' - 'A'; // 97 - 65 = 32;

	if((int)ch >= 97 && (int)ch <= 122 )
	{
		ac_c = (int)ch - idiff;
		return ((char)ac_c);
	}

	else
		return (ch);
}
