#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//variable declation
	char ac_InputString[AC_MAX_STRING_LENGTH];
	int ac_i;
	int istr_len = 0;

	int iac_CountA = 0;
	int iac_CountE = 0;
	int iac_CountI = 0;
	int iac_CountO = 0;
	int iac_CountU = 0;

	//code
	printf("\n");
	printf("Enter A String:");
	gets_s(ac_InputString, AC_MAX_STRING_LENGTH);
	
	printf("\n");
	printf("Entered String: %s",ac_InputString);

	istr_len = AcMyStringLength(ac_InputString);

	for(ac_i=0; ac_i < istr_len; ac_i++)
	{
		switch(ac_InputString[ac_i])
		{
			case 'a':
			case 'A':
				iac_CountA++;
				break;

			case 'e':
			case 'E':
				iac_CountE++;
				break;

			case 'i':
			case 'I':
				iac_CountI++;
				break;

			case 'o':
			case 'O':
				iac_CountO++;
				break;

			case 'u':
			case 'U':
				iac_CountU++;
				break;

			default:
				break;
		}
	}

	printf("\n\n");
	printf("Occurence of A/a: %d times\n", iac_CountA);
	printf("Occurence of E/e: %d times\n", iac_CountE);
	printf("Occurence of I/i: %d times\n", iac_CountI);
	printf("Occurence of O/o: %d times\n", iac_CountO);
	printf("Occurence of U/u: %d times\n", iac_CountU);

	return (0);
}

int AcMyStringLength(char str[])
{
	//variable declation
	int ac_i;
	int istr_len = 0;

	//code
	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			istr_len++;
	}
	return (istr_len);
}
