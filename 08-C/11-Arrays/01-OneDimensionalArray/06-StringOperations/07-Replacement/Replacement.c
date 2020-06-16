#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations/prototype
	int AcMyStrLen(char []);
	void AcMyStrCpy(char [],char []);

	//varaible declarations
	char ch_input_string[AC_MAX_STRING_LENGTH];
	char ch_replaced_string[AC_MAX_STRING_LENGTH];
	int istr_len;
	int ac_i;

	//code
	printf("\n");
	printf("Enter A string:");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	AcMyStrCpy(ch_replaced_string, ch_input_string);

	istr_len = AcMyStrLen(ch_replaced_string);

	for(ac_i = 0; ac_i < istr_len; ac_i++)
	{
		switch(ch_replaced_string[ac_i])
		{
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 'u':
			case 'U':
				ch_replaced_string[ac_i]='*';
				break;

			default:
				break;
		}
	}

	printf("\n");
	printf("Input String: %s\n", ch_input_string);

	printf("\n");
	printf("Wovels replaced by * String: %s\n", ch_replaced_string);

	return (0);
}

void AcMyStrCpy(char dest[], char src[])
{
	int ac_i;
	int istrlen;

	istrlen = AcMyStrLen(src); 
	for(ac_i = 0; ac_i < istrlen; ac_i++)
	{
		dest[ac_i] = src[ac_i];
	}

	dest[ac_i] = '\0';
}

int AcMyStrLen(char str[])
{
	int ac_i;
	int istrlen = 0;

	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			istrlen++;
	}
	return(istrlen);
}
