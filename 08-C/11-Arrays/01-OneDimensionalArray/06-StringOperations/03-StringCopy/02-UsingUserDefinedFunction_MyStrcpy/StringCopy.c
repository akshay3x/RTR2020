#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations/prototype
	void AcMyStrCpy(char[], char[]);
	
	//variable declaration
	char ch_ac_str_org[AC_MAX_STRING_LENGTH];
	char ch_ac_str_copy[AC_MAX_STRING_LENGTH];

	//code
	printf("\n");
	printf("Enter a String: ");
	gets_s(ch_ac_str_org, AC_MAX_STRING_LENGTH);

	//copying
	AcMyStrCpy(ch_ac_str_copy, ch_ac_str_org);

	printf("\n");
	printf("String entered: %s\n", ch_ac_str_org);

	printf("\n");
	printf("Copied String: %s\n", ch_ac_str_copy);

	return (0);
}

void AcMyStrCpy(char dest[], char src[])
{
	//function declarations/prototype
	int AcMyStrLen();

	//variable declarations
	int i_ac_strlen = 0;
	int ac_j = 0;

	i_ac_strlen = AcMyStrLen(src);

	for(ac_j=0; ac_j < i_ac_strlen; ac_j++)
	{
		dest[ac_j] = src[ac_j];
	}
	dest[ac_j] = '\0';

}

int AcMyStrLen(char str[])
{
	//variable declarations
	int i_ac_strlen = 0;
	int ac_j = 0;

	//code
	for(ac_j=0; ac_j < AC_MAX_STRING_LENGTH; ac_j++)
	{
		if(str[ac_j] == '\0')
			break;
		else
			i_ac_strlen++;
	}

	return (i_ac_strlen);
}
